import 'dotenv/config'
import { PrismaClient } from '../prisma/.prisma/client'
import { PrismaPg } from '@prisma/adapter-pg'
import express from 'express'
import cors from 'cors'
import { hashPassword, verifyPassword } from './auth'
// @ts-ignore - plain JS module without type declarations
import { ACHIEVEMENTS } from '../shared/Achievements.js'

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
    return res.status(400).json({ error: 'Username, email and password are required' })
  }

  // Validación básica del lado del servidor
  if (username.length < 3) {
    return res.status(400).json({ error: 'Username must have 3 characters' })
  }
  if (password.length < 6) {
    return res.status(400).json({ error: 'Pwd must have at least 6 chars' })
  }
  const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/
  if (!emailRegex.test(email)) {
    return res.status(400).json({ error: 'invalid Email' })
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
      return res.status(400).json({ error: 'Username or email already exist' })
    }
    res.status(500).json({ error: 'Error creating user' })
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
      return res.status(404).json({ error: 'User not found' })
    }
    res.status(500).json({ error: 'Error updating user' })
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
      return res.status(404).json({ error: 'Stadistics not found' })
    }
    res.json(stats)
  } catch (error) {
    res.status(500).json({ error: 'Error loading stadistics' })
  }
})

// POST /users/:username/stats/record-game - Atomic increment after a finished game
app.post('/users/:username/stats/record-game', async (req, res) => {
  const { username } = req.params
  const { won, territoriesConquered = 0, totalTurns = 0 } = req.body

  if (typeof won !== 'boolean') {
    return res.status(400).json({ error: 'won (boolean) is required' })
  }
  if (!Number.isInteger(territoriesConquered) || territoriesConquered < 0) {
    return res.status(400).json({ error: 'territoriesConquered must be a non-negative integer' })
  }
  if (!Number.isInteger(totalTurns) || totalTurns < 0) {
    return res.status(400).json({ error: 'totalTurns must be a non-negative integer' })
  }

  try {
    const stats = await prisma.stat.update({
      where: { username },
      data: {
        gamesPlayed: { increment: 1 },
        ...(won ? { wins: { increment: 1 } } : { losses: { increment: 1 } }),
        ...(territoriesConquered > 0 && { territoriesConquered: { increment: territoriesConquered } }),
        ...(totalTurns > 0 && { totalTurns: { increment: totalTurns } }),
      },
    })
    res.json(stats)
  } catch (error: any) {
    if (error.code === 'P2025') {
      return res.status(404).json({ error: 'User or stats not found' })
    }
    res.status(500).json({ error: 'Error recording game result' })
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
      return res.status(404).json({ error: 'Usuario or stats not found' })
    }
    res.status(500).json({ error: 'Error updating stats' })
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
    res.status(500).json({ error: 'Error finding friends' })
  }
})

// POST /users/:userUsername/friends/:friendUsername - Agregar amigo
app.post('/users/:userUsername/friends/:friendUsername', async (req, res) => {
  const { userUsername, friendUsername } = req.params

  if (userUsername === friendUsername) {
    return res.status(400).json({ error: 'You cannot be your own friend' })
  }

  try {
    // Verificar que ambos usuarios existan
    const [user, friend] = await Promise.all([
      prisma.user.findUnique({ where: { username: userUsername } }),
      prisma.user.findUnique({ where: { username: friendUsername } })
    ])

    if (!user || !friend) {
      return res.status(404).json({ error: 'One of both users dont exists' })
    }

    const reverse = await prisma.friendship.findUnique({
      where: {
        userUsername_friendUsername: {
          userUsername: friendUsername,
          friendUsername: userUsername
        }
      }
    })
    if (reverse) {
      return res.status(200).json(reverse)
    }

    const friendship = await prisma.friendship.create({
      data: {
        userUsername,
        friendUsername
      }
    })

    res.status(201).json(friendship)
  } catch (error: any) {
    if (error.code === 'P2002') {
      return res.status(400).json({ error: 'already friends' })
    }
    res.status(500).json({ error: 'Error adding friend' })
  }
})

// DELETE /users/:userUsername/friends/:friendUsername - Eliminar amigo
app.delete('/users/:userUsername/friends/:friendUsername', async (req, res) => {
  const { userUsername, friendUsername } = req.params

  try {
    const result = await prisma.friendship.deleteMany({
      where: {
        OR: [
          { userUsername, friendUsername },
          { userUsername: friendUsername, friendUsername: userUsername }
        ]
      }
    })
    if (result.count === 0) {
      return res.status(404).json({ error: 'friend not found' })
    }
    res.json({ message: 'Amistad eliminada', removed: result.count })
  } catch (error: any) {
    res.status(500).json({ error: 'Error removing friend' })
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
    res.status(500).json({ error: 'Error loading game' })
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
      return res.status(404).json({ error: 'Game not found' })
    }
    res.json(match)
  } catch (error) {
    res.status(500).json({ error: 'Error loading game' })
  }
})

// POST /matches - Crear partida nueva
app.post('/matches', async (req, res) => {
  const { gameMode, maxPlayers = 4, status = 'waiting', gameState } = req.body

  if (!gameMode) {
    return res.status(400).json({ error: 'gameMode is required' })
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
    res.status(500).json({ error: 'Error creating match' })
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
      return res.status(404).json({ error: 'Match not found' })
    }
    res.status(500).json({ error: 'Error updating match' })
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
      return res.status(404).json({ error: 'User not found' })
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
      return res.status(400).json({ error: 'User is already in match' })
    }
    res.status(500).json({ error: 'Error adding user to match' })
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
      return res.status(404).json({ error: 'Player not found in match' })
    }
    res.status(500).json({ error: 'Error updating player' })
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
      return res.status(404).json({ error: 'Player not found in match' })
    }

    res.json({ message: 'Jugador eliminado de partida' })
  } catch (error) {
    res.status(500).json({ error: 'Error removing player' })
  }
})

// PUT /matches/:id/gamestate - Actualizar estado de juego
app.put('/matches/:id/gamestate', async (req, res) => {
  const { id } = req.params
  const { gameState } = req.body

  if (!gameState) {
    return res.status(400).json({ error: 'gameState is required' })
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
      return res.status(404).json({ error: 'Match not found' })
    }
    res.status(500).json({ error: 'Error updating game' })
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
    res.status(500).json({ error: 'Error loading achievements' })
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
      return res.status(404).json({ error: 'Achievement not found' })
    }
    res.json(achievement)
  } catch (error) {
    res.status(500).json({ error: 'Error loading achievement' })
  }
})

// POST /achievements - Crear logro nuevo
app.post('/achievements', async (req, res) => {
  const { name, description } = req.body

  if (!name || !description) {
    return res.status(400).json({ error: 'name and description are necesary' })
  }

  try {
    const achievement = await prisma.achievement.create({
      data: { name, description }
    })
    res.status(201).json(achievement)
  } catch (error) {
    res.status(500).json({ error: 'Error creating achievement' })
  }
})

// POST /users/:username/achievements/:achievementNameId - Desbloquear logro
app.post('/users/:username/achievements/:achievementNameId', async (req, res) => {
  const { username, achievementNameId } = req.params

  try {
    // Verificar que el usuario existe
    const user = await prisma.user.findUnique({ where: { username } })
    if (!user) {
      return res.status(404).json({ error: 'User not found' })
    }
    const userAchievement = await prisma.userAchievement.create({
      data: {
        username,
        achievementNameId
      },
      include: {
        user: true,
        achievement: true
      }
    })
    res.status(201).json(userAchievement)
  } catch (error: any) {
    if (error.code === 'P2002') {
      return res.status(400).json({ error: 'User has this achievement' })
    }
    res.status(500).json({ error: 'Error unlock achievement' })
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
    res.status(500).json({ error: 'Error loading achievements' })
  }
})

// ============================================================================
// TRANSCENDENCE ENDPOINTS - Rooms (persistencia de partidas en curso)
// ============================================================================

// GET /rooms - Listar todas las salas (usado por engine al arrancar)
app.get('/rooms', async (_req, res) => {
  try {
    const rooms = await prisma.room.findMany()
    res.json(rooms)
  } catch (error) {
    res.status(500).json({ error: 'Error loading rooms' })
  }
})

// GET /rooms/:roomId - Obtener una sala
app.get('/rooms/:roomId', async (req, res) => {
  const { roomId } = req.params
  try {
    const room = await prisma.room.findUnique({ where: { roomId } })
    if (!room) return res.status(404).json({ error: 'Room not found' })
    res.json(room)
  } catch (error) {
    res.status(500).json({ error: 'Error loading room' })
  }
})

// PUT /rooms/:roomId - Upsert (create + lifecycle updates usan este endpoint)
app.put('/rooms/:roomId', async (req, res) => {
  const { roomId } = req.params
  const { maxPlayers, maxTurns, started, players, gameState } = req.body

  const data = {
    ...(maxPlayers !== undefined && { maxPlayers }),
    ...(maxTurns !== undefined && { maxTurns }),
    ...(started !== undefined && { started }),
    ...(players !== undefined && { players }),
    ...(gameState !== undefined && { gameState }),
  }

  try {
    const room = await prisma.room.upsert({
      where: { roomId },
      create: {
        roomId,
        maxPlayers: maxPlayers ?? 4,
        maxTurns: maxTurns ?? 100,
        started: started ?? false,
        players: players ?? [],
        gameState: gameState ?? null,
      },
      update: data,
    })
    res.json(room)
  } catch (error) {
    res.status(500).json({ error: 'Error saving room' })
  }
})

// DELETE /rooms/:roomId - Eliminar sala (al finalizar la partida)
app.delete('/rooms/:roomId', async (req, res) => {
  const { roomId } = req.params
  try {
    await prisma.room.delete({ where: { roomId } })
    res.json({ message: 'Room deleted' })
  } catch (error: any) {
    if (error.code === 'P2025') {
      return res.status(404).json({ error: 'Room not found' })
    }
    res.status(500).json({ error: 'Error deleting room' })
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
    return res.status(400).json({ error: 'Missing required fields' })
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
    if (error.code === 'P2002') return res.status(400).json({ error: 'Username or email already exist' })
    res.status(500).json({ error: 'Error registering' })
  }
})

app.post('/auth/login', async (req, res) => {
  const { email, password } = req.body
  if (!email || !password) {
    return res.status(400).json({ error: 'Missing required fiedls' })
  }
  try {
    const user = await prisma.user.findUnique({ where: { email } })
    if (!user) return res.status(401).json({ error: 'User not found' })

    const valid = await verifyPassword(password, user.passwordHash)
    if (!valid) return res.status(401).json({ error: 'Incomplete password' })

    const { passwordHash: _, ...safeUser } = user
    res.json({ ok: true, user: safeUser })
  } catch (error) {
    res.status(500).json({ error: 'Error login' })
  }
})

// Upsert the achievement definitions from shared/Achievements.js so the
// `achievements` table is always in sync with the gameplay source of truth.
// Runs once on boot; safe to re-run because upsert is idempotent.
async function seedAchievements() {
  const entries: any[] = Object.values(ACHIEVEMENTS as any)
  for (const a of entries) {
    await prisma.achievement.upsert({
      where: { nameId: a.id },
      create: { nameId: a.id, name: a.name, description: a.description },
      update: { name: a.name, description: a.description },
    })
  }
  console.log(`[database] seeded ${entries.length} achievements from shared/Achievements.js`)
}

// IIFE because this file is transpiled to CJS by tsx (no "type": "module" in
// package.json), so top-level await would fail to compile. The server still
// starts synchronously below; the seed runs in the background.
;(async () => {
  try {
    await seedAchievements()
  } catch (err: any) {
    console.error('[database] failed to seed achievements:', err?.message ?? err)
  }
})()

const PORT = parseInt(process.env.PORT || '4000')
const server = app.listen(PORT, () =>
  console.log(`
🚀 Server ready at: http://localhost:${PORT}
⭐️ See sample requests: https://github.com/prisma/prisma-examples/blob/latest/orm/express/README.md#using-the-rest-api`),
)
