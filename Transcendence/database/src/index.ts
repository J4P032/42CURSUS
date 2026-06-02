import 'dotenv/config'
import { Prisma, PrismaClient } from '../prisma/.prisma/client'
import { PrismaPg } from '@prisma/adapter-pg'
import express from 'express'
import bcrypt from 'bcrypt'
import cors from 'cors'

const pool = new PrismaPg({ connectionString: process.env.DATABASE_URL! })
const prisma = new PrismaClient({ adapter: pool })

const app = express()
app.use(cors())
app.use(express.json())

app.post(`/signup`, async (req, res) => {
  const { name, email, posts } = req.body

  const postData = posts?.map((post: Prisma.PostCreateInput) => {
    return { title: post?.title, content: post?.content }
  })

  const result = await prisma.user.create({
    data: {
      name,
      email,
      posts: {
        create: postData,
      },
    },
  })
  res.json(result)
})

app.post(`/post`, async (req, res) => {
  const { title, content, authorEmail } = req.body
  const result = await prisma.post.create({
    data: {
      title,
      content,
      author: { connect: { email: authorEmail } },
    },
  })
  res.json(result)
})

app.put('/post/:id/views', async (req, res) => {
  const { id } = req.params

  try {
    const post = await prisma.post.update({
      where: { id: Number(id) },
      data: {
        viewCount: {
          increment: 1,
        },
      },
    })

    res.json(post)
  } catch (error) {
    res.json({ error: `Post with ID ${id} does not exist in the database` })
  }
})

app.put('/publish/:id', async (req, res) => {
  const { id } = req.params

  try {
    const postData = await prisma.post.findUnique({
      where: { id: Number(id) },
      select: {
        published: true,
      },
    })

    const updatedPost = await prisma.post.update({
      where: { id: Number(id) || undefined },
      data: { published: !postData?.published },
    })
    res.json(updatedPost)
  } catch (error) {
    res.json({ error: `Post with ID ${id} does not exist in the database` })
  }
})

app.delete(`/post/:id`, async (req, res) => {
  const { id } = req.params
  const post = await prisma.post.delete({
    where: {
      id: Number(id),
    },
  })
  res.json(post)
})

app.get('/users', async (req, res) => {
  const users = await prisma.user.findMany()
  res.json(users)
})

app.get('/user/:id/drafts', async (req, res) => {
  const { id } = req.params

  const drafts = await prisma.post.findMany({
    where: {
      authorId: Number(id),
      published: false,
    },
  })

  res.json(drafts)
})

app.get(`/post/:id`, async (req, res) => {
  const { id }: { id?: string } = req.params

  const post = await prisma.post.findUnique({
    where: { id: Number(id) },
  })
  res.json(post)
})

app.get('/feed', async (req, res) => {
  const { searchString, skip, take, orderBy } = req.query

  const or: Prisma.PostWhereInput = searchString
    ? {
      OR: [
        { title: { contains: searchString as string } },
        { content: { contains: searchString as string } },
      ],
    }
    : {}

  const posts = await prisma.post.findMany({
    where: {
      published: true,
      ...or,
    },
    include: { author: true },
    take: Number(take) || undefined,
    skip: Number(skip) || undefined,
    orderBy: {
      updatedAt: orderBy as Prisma.SortOrder,
    },
  })

  res.json(posts)
})

// ============================================================================
// TRANSCENDENCE ENDPOINTS - Users
// ============================================================================

// GET /users/:id - Obtener usuario específico con relaciones
app.get('/users/:id', async (req, res) => {
  const { id } = req.params
  try {
    const user = await prisma.user.findUnique({
      where: { id: Number(id) },
      include: {
        stats: true,
        friendshipsAsUser: {
          include: { friend: true }
        },
        friendshipsAsFriend: {
          include: { user: true }
        },
        userAchievements: {
          include: { achievement: true }
        },
        matchPlayers: {
          include: { match: true }
        }
      }
    })
    
    if (!user) {
      return res.status(404).json({ error: 'Usuario no encontrado' })
    }
    res.json(user)
  } catch (error) {
    res.status(500).json({ error: 'Error al obtener usuario' })
  }
});


// POST /users - Crear usuario nuevo
//creado en register de bcrypt.

// PUT /users/:id - Actualizar usuario
app.put('/users/:id', async (req, res) => {
  const { id } = req.params
  const { username, email, avatarUrl } = req.body

  try {
    const user = await prisma.user.update({
      where: { id: Number(id) },
      data: {
        ...(username && { username }),
        ...(email && { email }),
        ...(avatarUrl && { avatarUrl })
      },
      include: { stats: true }
    })
    res.json(user)
  } catch (error: any) {
    if (error.code === 'P2025') {
      return res.status(404).json({ error: 'Usuario no encontrado' })
    }
    res.status(500).json({ error: 'Error al actualizar usuario' })
  }
})

// ============================================================================
// TRANSCENDENCE ENDPOINTS - Stats
// ============================================================================

// GET /users/:id/stats - Obtener estadísticas de usuario
app.get('/users/:id/stats', async (req, res) => {
  const { id } = req.params
  try {
    const stats = await prisma.stat.findUnique({
      where: { userId: Number(id) }
    })
    
    if (!stats) {
      return res.status(404).json({ error: 'Estadísticas no encontradas' })
    }
    res.json(stats)
  } catch (error) {
    res.status(500).json({ error: 'Error al obtener estadísticas' })
  }
})

// PUT /users/:id/stats - Actualizar estadísticas
app.put('/users/:id/stats', async (req, res) => {
  const { id } = req.params
  const { gamesPlayed, wins, losses, elo } = req.body

  try {
    const stats = await prisma.stat.update({
      where: { userId: Number(id) },
      data: {
        ...(gamesPlayed !== undefined && { gamesPlayed }),
        ...(wins !== undefined && { wins }),
        ...(losses !== undefined && { losses }),
        ...(elo !== undefined && { elo })
      }
    })
    res.json(stats)
  } catch (error: any) {
    if (error.code === 'P2025') {
      return res.status(404).json({ error: 'Usuario o estadísticas no encontradas' })
    }
    res.status(500).json({ error: 'Error al actualizar estadísticas' })
  }
})

// ============================================================================
// TRANSCENDENCE ENDPOINTS - Friendships
// ============================================================================

// GET /users/:id/friends - Obtener amigos de usuario
app.get('/users/:id/friends', async (req, res) => {
  const { id } = req.params
  try {
    const friendshipsAs = await prisma.friendship.findMany({
      where: { userId: Number(id) },
      include: { friend: true }
    })

    const friendshipsAsFriend = await prisma.friendship.findMany({
      where: { friendId: Number(id) },
      include: { user: true }
    })

    const friends = [
      ...friendshipsAs.map(f => ({ ...f.friend, since: f.createdAt })),
      ...friendshipsAsFriend.map(f => ({ ...f.user, since: f.createdAt }))
    ]

    res.json(friends)
  } catch (error) {
    res.status(500).json({ error: 'Error al obtener amigos' })
  }
})

// POST /users/:userId/friends/:friendId - Agregar amigo
app.post('/users/:userId/friends/:friendId', async (req, res) => {
  const { userId, friendId } = req.params

  if (userId === friendId) {
    return res.status(400).json({ error: 'No puedes ser amigo de ti mismo' })
  }

  try {
    // Verificar que ambos usuarios existan
    const [user, friend] = await Promise.all([
      prisma.user.findUnique({ where: { id: Number(userId) } }),
      prisma.user.findUnique({ where: { id: Number(friendId) } })
    ])

    if (!user || !friend) {
      return res.status(404).json({ error: 'Uno o ambos usuarios no existen' })
    }

    // Crear amistad (solo una dirección)
    const friendship = await prisma.friendship.create({
      data: {
        userId: Number(userId),
        friendId: Number(friendId)
      }
    })

    res.status(201).json(friendship)
  } catch (error: any) {
    if (error.code === 'P2002') {
      return res.status(400).json({ error: 'Ya son amigos' })
    }
    res.status(500).json({ error: 'Error al agregar amigo' })
  }
})

// DELETE /users/:userId/friends/:friendId - Eliminar amigo
app.delete('/users/:userId/friends/:friendId', async (req, res) => {
  const { userId, friendId } = req.params

  try {
    const friendship = await prisma.friendship.delete({
      where: {
        userId_friendId: {
          userId: Number(userId),
          friendId: Number(friendId)
        }
      }
    })
    res.json({ message: 'Amistad eliminada', friendship })
  } catch (error: any) {
    if (error.code === 'P2025') {
      return res.status(404).json({ error: 'Amistad no encontrada' })
    }
    res.status(500).json({ error: 'Error al eliminar amistad' })
  }
})

// ============================================================================
// TRANSCENDENCE ENDPOINTS - Matches
// ============================================================================

// GET /matches - Obtener todas las partidas
app.get('/matches', async (req, res) => {
  const { status, gameMode, skip = '0', take = '10' } = req.query

  try {
    const matches = await prisma.match.findMany({
      where: {
        ...(status && { status: String(status) }),
        ...(gameMode && { gameMode: String(gameMode) })
      },
      include: {
        matchPlayers: {
          include: { user: true }
        }
      },
      skip: Number(skip),
      take: Number(take),
      orderBy: { createdAt: 'desc' }
    })

    res.json(matches)
  } catch (error) {
    res.status(500).json({ error: 'Error al obtener partidas' })
  }
})

// GET /matches/:id - Obtener partida específica
app.get('/matches/:id', async (req, res) => {
  const { id } = req.params

  try {
    const match = await prisma.match.findUnique({
      where: { id: Number(id) },
      include: {
        matchPlayers: {
          include: { user: true },
          orderBy: { score: 'desc' }
        }
      }
    })

    if (!match) {
      return res.status(404).json({ error: 'Partida no encontrada' })
    }
    res.json(match)
  } catch (error) {
    res.status(500).json({ error: 'Error al obtener partida' })
  }
})

// POST /matches - Crear partida nueva
app.post('/matches', async (req, res) => {
  const { gameMode, maxPlayers = 4, status = 'waiting' } = req.body

  if (!gameMode) {
    return res.status(400).json({ error: 'gameMode es requerido' })
  }

  try {
    const match = await prisma.match.create({
      data: {
        gameMode,
        maxPlayers,
        status
      }
    })
    res.status(201).json(match)
  } catch (error) {
    res.status(500).json({ error: 'Error al crear partida' })
  }
})

// PUT /matches/:id - Actualizar partida
app.put('/matches/:id', async (req, res) => {
  const { id } = req.params
  const { status, startedAt, endedAt } = req.body

  try {
    const match = await prisma.match.update({
      where: { id: Number(id) },
      data: {
        ...(status && { status }),
        ...(startedAt && { startedAt: new Date(startedAt) }),
        ...(endedAt && { endedAt: new Date(endedAt) })
      },
      include: { matchPlayers: true }
    })
    res.json(match)
  } catch (error: any) {
    if (error.code === 'P2025') {
      return res.status(404).json({ error: 'Partida no encontrada' })
    }
    res.status(500).json({ error: 'Error al actualizar partida' })
  }
})

// POST /matches/:matchId/players/:userId - Agregar jugador a partida
app.post('/matches/:matchId/players/:userId', async (req, res) => {
  const { matchId, userId } = req.params
  const { score = 0, position } = req.body

  try {
    const matchPlayer = await prisma.matchPlayer.create({
      data: {
        matchId: Number(matchId),
        userId: Number(userId),
        score,
        position: position ? Number(position) : null
      },
      include: { user: true, match: true }
    })
    res.status(201).json(matchPlayer)
  } catch (error: any) {
    if (error.code === 'P2002') {
      return res.status(400).json({ error: 'El usuario ya está en esta partida' })
    }
    res.status(500).json({ error: 'Error al agregar jugador a partida' })
  }
})

// PUT /match-players/:id - Actualizar datos del jugador en partida
app.put('/match-players/:id', async (req, res) => {
  const { id } = req.params
  const { score, position } = req.body

  try {
    const matchPlayer = await prisma.matchPlayer.update({
      where: { id: Number(id) },
      data: {
        ...(score !== undefined && { score }),
        ...(position !== undefined && { position })
      },
      include: { user: true, match: true }
    })
    res.json(matchPlayer)
  } catch (error: any) {
    if (error.code === 'P2025') {
      return res.status(404).json({ error: 'Jugador en partida no encontrado' })
    }
    res.status(500).json({ error: 'Error al actualizar jugador' })
  }
})

// DELETE /matches/:matchId/players/:userId - Eliminar jugador de partida
app.delete('/matches/:matchId/players/:userId', async (req, res) => {
  const { matchId, userId } = req.params

  try {
    const deleted = await prisma.matchPlayer.deleteMany({
      where: {
        matchId: Number(matchId),
        userId: Number(userId)
      }
    })

    if (deleted.count === 0) {
      return res.status(404).json({ error: 'Jugador no encontrado en partida' })
    }

    res.json({ message: 'Jugador eliminado de partida' })
  } catch (error) {
    res.status(500).json({ error: 'Error al eliminar jugador' })
  }
})

// ============================================================================
// TRANSCENDENCE ENDPOINTS - Achievements
// ============================================================================

// GET /achievements - Obtener todos los logros
app.get('/achievements', async (req, res) => {
  try {
    const achievements = await prisma.achievement.findMany()
    res.json(achievements)
  } catch (error) {
    res.status(500).json({ error: 'Error al obtener logros' })
  }
})

// GET /achievements/:id - Obtener logro específico
app.get('/achievements/:id', async (req, res) => {
  const { id } = req.params

  try {
    const achievement = await prisma.achievement.findUnique({
      where: { id: Number(id) },
      include: {
        userAchievements: {
          include: { user: true }
        }
      }
    })

    if (!achievement) {
      return res.status(404).json({ error: 'Logro no encontrado' })
    }
    res.json(achievement)
  } catch (error) {
    res.status(500).json({ error: 'Error al obtener logro' })
  }
})

// POST /achievements - Crear logro nuevo
app.post('/achievements', async (req, res) => {
  const { name, description } = req.body

  if (!name || !description) {
    return res.status(400).json({ error: 'name y description son requeridos' })
  }

  try {
    const achievement = await prisma.achievement.create({
      data: { name, description }
    })
    res.status(201).json(achievement)
  } catch (error) {
    res.status(500).json({ error: 'Error al crear logro' })
  }
})

// POST /users/:userId/achievements/:achievementName_id - Desbloquear logro
app.post('/users/:userId/achievements/:achievementName_id', async (req, res) => {
  const { userId, achievementName_id } = req.params

  try {
    const userAchievement = await prisma.userAchievement.create({
      data: {
        userId: Number(userId),
        achievementName_id: achievementName_id
      },
      include: {
        user: true,
        achievement: true
      }
    })
    res.status(201).json(userAchievement)
  } catch (error: any) {
    if (error.code === 'P2002') {
      return res.status(400).json({ error: 'El usuario ya tiene este logro' })
    }
    res.status(500).json({ error: 'Error al desbloquear logro' })
  }
})

// GET /users/:userId/achievements - Obtener logros de usuario
app.get('/users/:userId/achievements', async (req, res) => {
  const { userId } = req.params

  try {
    const achievements = await prisma.userAchievement.findMany({
      where: { userId: Number(userId) },
      include: { achievement: true }
    })
    res.json(achievements)
  } catch (error) {
    res.status(500).json({ error: 'Error al obtener logros' })
  }
})

//Registro del usuario
app.post('/auth/register', async (req, res) => {
  const { email, username, password } = req.body;
  try {
    const hashedPassword = await bcrypt.hash(password, 10); //10 2^10 lo que tarda para evitar Hacks automaticos
    const user = await prisma.user.create({
      data: {
        email,
        username,
        passwordHash: hashedPassword, //contraseña cifrada por bcrypt
        stats: { create: { gamesPlayed: 0, wins: 0, losses: 0, elo: 1000 } }
      }
    });
    res.json({ ok: true, user: { id: user.id, username: user.username } });
  } catch (error: any) {
    if (error.code === 'P2002') return res.status(400).json({ ok: false, error: 'Email/User ya existe' });
    res.status(500).json({ ok: false, error: 'Error en el servidor' });
  }
});

//login del usuario
app.post('/auth/login', async (req, res) => {
  const { email, password } = req.body;
  try {
    const user = await prisma.user.findUnique({ where: { email } });
    if (!user || !user.passwordHash) return res.status(401).json({ ok: false, error: 'Usuario no encontrado' });

    const check = await bcrypt.compare(password, user.passwordHash);
    if (!check) return res.status(401).json({ ok: false, error: 'Contraseña incorrecta' });

    res.json({ ok: true, user: { id: user.id, username: user.username } });
  } catch (error) {
    res.status(500).json({ ok: false, error: 'Error en el servidor' });
  }
});


// Health check endpoint para Docker
app.get('/health', (req, res) => {
  res.status(200).json({ status: 'ok' })
})

const PORT = parseInt(process.env.PORT || '4000')
const server = app.listen(PORT, () =>
  console.log(`
🚀 Server ready at: http://localhost:${PORT}
⭐️ See sample requests: https://github.com/prisma/prisma-examples/blob/latest/orm/express/README.md#using-the-rest-api`),
)
