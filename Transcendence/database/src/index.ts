import 'dotenv/config'
import { PrismaClient } from '../prisma/.prisma/client'
import { PrismaPg } from '@prisma/adapter-pg'
import express from 'express'
import cors from 'cors'
import { hashPassword, verifyPassword } from './auth'

const pool = new PrismaPg({ connectionString: process.env.DATABASE_URL! })
const prisma = new PrismaClient({ adapter: pool })

const app = express()

app.use(cors())
app.use(express.json())

// ============================================================================
// TRANSCENDENCE ENDPOINTS - Users
// ============================================================================

// GET /users/:username - Obtener usuario específico con relaciones
app.get('/users/:username', async (req, res) => {
  const { username } = req.params
  try {
    const user = await prisma.user.findUnique({
      where: { username },
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
})

// POST /users - Crear usuario nuevo
app.post('/users', async (req, res) => {
  const { username, email, password, avatarUrl } = req.body

  if (!username || !email || !password) {
    return res.status(400).json({ error: 'username, email y password son requeridos' })
  }

  try {
    const passwordHash = await hashPassword(password)
    const user = await prisma.user.create({
      data: {
        username,
        email,
        passwordHash,
        avatarUrl,
        stats: {
          create: {
            gamesPlayed: 0,
            wins: 0,
            losses: 0,
            elo: 1000
          }
        }
      },
      include: { stats: true }
    })
    res.status(201).json(user)
  } catch (error: any) {
    if (error.code === 'P2002') {
      return res.status(400).json({ error: 'Username o email ya existe' })
    }
    res.status(500).json({ error: 'Error al crear usuario' })
  }
})

// PUT /users/:username - Actualizar usuario
app.put('/users/:username', async (req, res) => {
  const { username } = req.params
  const { email, avatarUrl } = req.body

  try {
    const user = await prisma.user.update({
      where: { username },
      data: {
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

// GET /users/:username/stats - Obtener estadísticas de usuario
app.get('/users/:username/stats', async (req, res) => {
  const { username } = req.params
  try {
    const stats = await prisma.stat.findUnique({
      where: { username }
    })
    
    if (!stats) {
      return res.status(404).json({ error: 'Estadísticas no encontradas' })
    }
    res.json(stats)
  } catch (error) {
    res.status(500).json({ error: 'Error al obtener estadísticas' })
  }
})

// PUT /users/:username/stats - Actualizar estadísticas
app.put('/users/:username/stats', async (req, res) => {
  const { username } = req.params
  const { gamesPlayed, wins, losses, elo } = req.body

  try {
    const stats = await prisma.stat.update({
      where: { username },
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

// GET /users/:username/friends - Obtener amigos de usuario
app.get('/users/:username/friends', async (req, res) => {
  const { username } = req.params
  try {
    const friendshipsAs = await prisma.friendship.findMany({
      where: { userUsername: username },
      include: { friend: true }
    })

    const friendshipsAsFriend = await prisma.friendship.findMany({
      where: { friendUsername: username },
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

// POST /users/:userUsername/friends/:friendUsername - Agregar amigo
app.post('/users/:userUsername/friends/:friendUsername', async (req, res) => {
  const { userUsername, friendUsername } = req.params

  if (userUsername === friendUsername) {
    return res.status(400).json({ error: 'No puedes ser amigo de ti mismo' })
  }

  try {
    // Verificar que ambos usuarios existan
    const [user, friend] = await Promise.all([
      prisma.user.findUnique({ where: { username: userUsername } }),
      prisma.user.findUnique({ where: { username: friendUsername } })
    ])

    if (!user || !friend) {
      return res.status(404).json({ error: 'Uno o ambos usuarios no existen' })
    }

    // Crear amistad (solo una dirección)
    const friendship = await prisma.friendship.create({
      data: {
        userUsername,
        friendUsername
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

// DELETE /users/:userUsername/friends/:friendUsername - Eliminar amigo
app.delete('/users/:userUsername/friends/:friendUsername', async (req, res) => {
  const { userUsername, friendUsername } = req.params

  try {
    const friendship = await prisma.friendship.delete({
      where: {
        userUsername_friendUsername: {
          userUsername,
          friendUsername
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
  const { gameMode, maxPlayers = 4, status = 'waiting', gameState } = req.body

  if (!gameMode) {
    return res.status(400).json({ error: 'gameMode es requerido' })
  }

  try {
    const match = await prisma.match.create({
      data: {
        gameMode,
        maxPlayers,
        status,
        ...(gameState && { gameState })
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
  const { status, startedAt, endedAt, gameState } = req.body

  try {
    const match = await prisma.match.update({
      where: { id: Number(id) },
      data: {
        ...(status && { status }),
        ...(startedAt && { startedAt: new Date(startedAt) }),
        ...(endedAt && { endedAt: new Date(endedAt) }),
        ...(gameState && { gameState })
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

// POST /matches/:matchId/players/:username - Agregar jugador a partida
app.post('/matches/:matchId/players/:username', async (req, res) => {
  const { matchId, username } = req.params
  const { score = 0, position } = req.body

  try {
    // Verificar que el usuario existe
    const user = await prisma.user.findUnique({ where: { username } })
    if (!user) {
      return res.status(404).json({ error: 'Usuario no encontrado' })
    }
    const matchPlayer = await prisma.matchPlayer.create({
      data: {
        matchId: Number(matchId),
        username,
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

// DELETE /matches/:matchId/players/:username - Eliminar jugador de partida
app.delete('/matches/:matchId/players/:username', async (req, res) => {
  const { matchId, username } = req.params

  try {
    const deleted = await prisma.matchPlayer.deleteMany({
      where: {
        matchId: Number(matchId),
        username
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

// PUT /matches/:id/gamestate - Actualizar estado de juego
app.put('/matches/:id/gamestate', async (req, res) => {
  const { id } = req.params
  const { gameState } = req.body

  if (!gameState) {
    return res.status(400).json({ error: 'gameState es requerido' })
  }

  try {
    const match = await prisma.match.update({
      where: { id: Number(id) },
      data: { gameState },
      include: { matchPlayers: { include: { user: true } } }
    })
    res.json(match)
  } catch (error: any) {
    if (error.code === 'P2025') {
      return res.status(404).json({ error: 'Partida no encontrada' })
    }
    res.status(500).json({ error: 'Error al actualizar estado de juego' })
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

// POST /users/:username/achievements/:achievementName_id - Desbloquear logro
app.post('/users/:username/achievements/:achievementName_id', async (req, res) => {
  const { username, achievementName_id } = req.params

  try {
    // Verificar que el usuario existe
    const user = await prisma.user.findUnique({ where: { username } })
    if (!user) {
      return res.status(404).json({ error: 'Usuario no encontrado' })
    }
    const userAchievement = await prisma.userAchievement.create({
      data: {
        username,
        achievementName_id
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

// GET /users/:username/achievements - Obtener logros de usuario
app.get('/users/:username/achievements', async (req, res) => {
  const { username } = req.params

  try {
    const achievements = await prisma.userAchievement.findMany({
      where: { username },
      include: { achievement: true }
    })
    res.json(achievements)
  } catch (error) {
    res.status(500).json({ error: 'Error al obtener logros' })
  }
})

// Health check endpoint para Docker
app.get('/health', (req, res) => {
  res.status(200).json({ status: 'ok' })
})

// ============================================================================
// AUTH ENDPOINTS (For frontend compatibility)
// ============================================================================

app.post('/auth/register', async (req, res) => {
  const { username, email, password, avatarUrl } = req.body
  if (!username || !email || !password) {
    return res.status(400).json({ error: 'Faltan campos requeridos' })
  }
  try {
    const passwordHash = await hashPassword(password)
    const user = await prisma.user.create({
      data: {
        username,
        email,
        passwordHash,
        avatarUrl,
        stats: { create: {} }
      }
    })
    const { passwordHash: _, ...safeUser } = user
    res.status(201).json({ ok: true, user: safeUser })
  } catch (error: any) {
    if (error.code === 'P2002') return res.status(400).json({ error: 'Username o email ya existe' })
    res.status(500).json({ error: 'Error al registrar' })
  }
})

app.post('/auth/login', async (req, res) => {
  const { email, password } = req.body
  if (!email || !password) {
    return res.status(400).json({ error: 'Faltan campos requeridos' })
  }
  try {
    const user = await prisma.user.findUnique({ where: { email } })
    if (!user) return res.status(401).json({ error: 'Usuario no encontrado' })

    const valid = await verifyPassword(password, user.passwordHash)
    if (!valid) return res.status(401).json({ error: 'Password incorrecto' })

    const { passwordHash: _, ...safeUser } = user
    res.json({ ok: true, user: safeUser })
  } catch (error) {
    res.status(500).json({ error: 'Error login' })
  }
})

const PORT = parseInt(process.env.PORT || '4000')
const server = app.listen(PORT, () =>
  console.log(`
🚀 Server ready at: http://localhost:${PORT}
⭐️ See sample requests: https://github.com/prisma/prisma-examples/blob/latest/orm/express/README.md#using-the-rest-api`),
)
