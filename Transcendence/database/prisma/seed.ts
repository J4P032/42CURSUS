import { Prisma, PrismaClient } from '../prisma/.prisma/client'
import { PrismaPg } from '@prisma/adapter-pg'
import * as crypto from 'crypto'

const pool = new PrismaPg({ connectionString: process.env.DATABASE_URL! })
const prisma = new PrismaClient({ adapter: pool })

// Función simple para generar un hash (puedes usar bcryptjs si lo instalas)
function hashPassword(password: string): string {
  return crypto.createHash('sha256').update(password).digest('hex')
}

// Datos base de usuarios de prueba (sin passwordHash aún)
const usersBase = [
  {
    username: 'shadow_lord',
    email: 'shadow@transcendence.io',
    password: 'password123',
    avatarUrl: 'https://api.dicebear.com/7.x/avataaars/svg?seed=shadow_lord',
    stats: {
      gamesPlayed: 45,
      wins: 32,
      losses: 13,
      elo: 1850,
    },
  },
  {
    username: 'crystal_queen',
    email: 'crystal@transcendence.io',
    password: 'password123',
    avatarUrl: 'https://api.dicebear.com/7.x/avataaars/svg?seed=crystal_queen',
    stats: {
      gamesPlayed: 38,
      wins: 28,
      losses: 10,
      elo: 1720,
    },
  },
  {
    username: 'phoenix_rider',
    email: 'phoenix@transcendence.io',
    password: 'password123',
    avatarUrl: 'https://api.dicebear.com/7.x/avataaars/svg?seed=phoenix_rider',
    stats: {
      gamesPlayed: 52,
      wins: 35,
      losses: 17,
      elo: 1650,
    },
  },
  {
    username: 'storm_bringer',
    email: 'storm@transcendence.io',
    password: 'password123',
    avatarUrl: 'https://api.dicebear.com/7.x/avataaars/svg?seed=storm_bringer',
    stats: {
      gamesPlayed: 28,
      wins: 15,
      losses: 13,
      elo: 1500,
    },
  },
  {
    username: 'dragon_slayer',
    email: 'dragon@transcendence.io',
    password: 'password123',
    avatarUrl: 'https://api.dicebear.com/7.x/avataaars/svg?seed=dragon_slayer',
    stats: {
      gamesPlayed: 15,
      wins: 8,
      losses: 7,
      elo: 1300,
    },
  },
]

// Datos de logros
const achievementData: Prisma.AchievementCreateInput[] = [
  {
    name_id: 'first_blood',
    name: 'First Blood',
    description: 'Win your first match',
  },
  {
    name_id: 'conqueror',
    name: 'Conqueror',
    description: 'Win 10 matches',
  },
  {
    name_id: 'legend',
    name: 'Legend',
    description: 'Reach ELO 1500',
  },
  {
    name_id: 'dominator',
    name: 'Dominator',
    description: 'Win 25 matches',
  },
  {
    name_id: 'undefeated',
    name: 'Undefeated',
    description: 'Win 5 consecutive matches',
  },
  {
    name_id: 'social_butterfly',
    name: 'Social Butterfly',
    description: 'Add 5 friends',
  },
]

async function main() {
  console.log(`🚀 Iniciando seeding de la base de datos...`)

  try {

    // Comprobar si ya hay usuarios. J4P032 borraba usuarios registrados
    const userCount = await prisma.user.count()
    if (userCount > 0) {
       console.log('✅ Base de datos ya tiene usuarios, saltando seeding para preservar datos.')
      return
    }
    // Limpiar datos existentes (en orden inverso por relaciones)
    console.log('🗑️  Base de datos vacía. Iniciando limpieza por seguridad...')
    await prisma.userAchievement.deleteMany()
    await prisma.achievement.deleteMany()
    await prisma.matchPlayer.deleteMany()
    await prisma.match.deleteMany()
    await prisma.friendship.deleteMany()
    await prisma.stat.deleteMany()
    await prisma.user.deleteMany()

    // Crear usuarios
    console.log('👥 Creando usuarios...')
    const users: any[] = []
    for (const u of usersBase) {
      const user = await prisma.user.create({
        data: {
          username: u.username,
          email: u.email,
          passwordHash: hashPassword(u.password),
          avatarUrl: u.avatarUrl,
          stats: {
            create: u.stats,
          },
        },
        include: { stats: true },
      })
      users.push(user)
      console.log(
        `   ✓ Usuario creado: ${user.username} (ID: ${user.id}) - ELO: ${user.stats?.elo}`
      )
    }

    // Crear logros
    console.log('🏆 Creando logros...')
    const achievements: any[] = []
    for (const achievement of achievementData) {
      const created = await prisma.achievement.create({
        data: achievement,
      })
      achievements.push(created)
      console.log(`   ✓ Logro creado: ${created.name}`)
    }

    // Crear amistades
    console.log('🤝 Creando amistades...')
    const friendships = [
      { userId: users[0].id, friendId: users[1].id },
      { userId: users[0].id, friendId: users[2].id },
      { userId: users[1].id, friendId: users[2].id },
      { userId: users[2].id, friendId: users[3].id },
      { userId: users[3].id, friendId: users[4].id },
    ]

    for (const friendship of friendships) {
      await prisma.friendship.create({
        data: friendship,
      })
      console.log(
        `   ✓ Amistad: usuario ${friendship.userId} <-> ${friendship.friendId}`
      )
    }

    // Crear partidas
    console.log('🎮 Creando partidas...')
    const matches = [
      {
        gameMode: 'Battle Royale',
        maxPlayers: 4,
        status: 'completed',
        startedAt: new Date(Date.now() - 7 * 24 * 60 * 60 * 1000),
        endedAt: new Date(Date.now() - 7 * 24 * 60 * 60 * 1000 + 20 * 60 * 1000),
      },
      {
        gameMode: 'Conquest',
        maxPlayers: 2,
        status: 'completed',
        startedAt: new Date(Date.now() - 3 * 24 * 60 * 60 * 1000),
        endedAt: new Date(Date.now() - 3 * 24 * 60 * 60 * 1000 + 15 * 60 * 1000),
      },
      {
        gameMode: 'Deathmatch',
        maxPlayers: 4,
        status: 'active',
        startedAt: new Date(Date.now() - 30 * 60 * 1000),
      },
      {
        gameMode: 'Territory Control',
        maxPlayers: 4,
        status: 'waiting',
      },
    ]

    const createdMatches: any[] = []
    for (const match of matches) {
      const created = await prisma.match.create({
        data: match as any,
      })
      createdMatches.push(created)
      console.log(`   ✓ Partida creada: ${created.gameMode} (ID: ${created.id})`)
    }

    // Crear jugadores en partidas
    console.log('🏅 Asignando jugadores a partidas...')
    const matchPlayers = [
      {
        matchId: createdMatches[0].id,
        userId: users[0].id,
        score: 2500,
        position: 1,
      },
      {
        matchId: createdMatches[0].id,
        userId: users[1].id,
        score: 2100,
        position: 2,
      },
      {
        matchId: createdMatches[0].id,
        userId: users[2].id,
        score: 1800,
        position: 3,
      },
      {
        matchId: createdMatches[0].id,
        userId: users[3].id,
        score: 1500,
        position: 4,
      },
      {
        matchId: createdMatches[1].id,
        userId: users[0].id,
        score: 3200,
        position: 1,
      },
      {
        matchId: createdMatches[1].id,
        userId: users[2].id,
        score: 2100,
        position: 2,
      },
      { matchId: createdMatches[2].id, userId: users[1].id, score: 1200 },
      { matchId: createdMatches[2].id, userId: users[3].id, score: 950 },
      { matchId: createdMatches[2].id, userId: users[4].id, score: 800 },
      { matchId: createdMatches[3].id, userId: users[0].id, score: 0 },
      { matchId: createdMatches[3].id, userId: users[1].id, score: 0 },
    ]

    for (const mp of matchPlayers) {
      await prisma.matchPlayer.create({
        data: mp as any,
      })
    }
    console.log(`   ✓ ${matchPlayers.length} jugadores asignados a partidas`)

    // Asignar logros a usuarios
    console.log('🎖️  Asignando logros a usuarios...')
    const userAchievements = [
      { userusername: users[0].username, achievementName_id: achievements[0].name_id },
      { userusername: users[0].username, achievementName_id: achievements[1].name_id },
      { userusername: users[0].username, achievementName_id: achievements[2].name_id },
      { userusername: users[1].username, achievementName_id: achievements[0].name_id },
      { userusername: users[1].username, achievementName_id: achievements[1].name_id },
      { userusername: users[2].username, achievementName_id: achievements[0].name_id },
    ]

    for (const ua of userAchievements) {
      await prisma.userAchievement.create({
        data: ua as any,
      })
    }
    console.log(`   ✓ ${userAchievements.length} logros asignados`)

    console.log('\n✅ Seeding completado exitosamente!')
    console.log(`\n📊 Resumen:`)
    console.log(`   - ${users.length} usuarios creados`)
    console.log(`   - ${achievements.length} logros creados`)
    console.log(`   - ${friendships.length} amistades creadas`)
    console.log(`   - ${createdMatches.length} partidas creadas`)
    console.log(`   - ${matchPlayers.length} jugadores en partidas`)
  } catch (error) {
    console.error('❌ Error durante el seeding:', error)
    throw error
  }
}

main()
  .then(async () => {
    await prisma.$disconnect()
  })
  .catch(async (e) => {
    console.error(e)
    await prisma.$disconnect()
    process.exit(1)
  })

