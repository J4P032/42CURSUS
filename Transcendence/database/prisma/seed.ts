import { Prisma, PrismaClient } from '../prisma/.prisma/client'
import { PrismaPg } from '@prisma/adapter-pg'
import { hashPassword } from '../src/auth'

const pool = new PrismaPg({ connectionString: process.env.DATABASE_URL! })
const prisma = new PrismaClient({ adapter: pool })

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
    nameId: 'first_blood',
    name: 'First Blood',
    description: 'Win your first match',
  },
  {
    nameId: 'conqueror',
    name: 'Conqueror',
    description: 'Win 10 matches',
  },
  {
    nameId: 'legend',
    name: 'Legend',
    description: 'Reach ELO 1500',
  },
  {
    nameId: 'dominator',
    name: 'Dominator',
    description: 'Win 25 matches',
  },
  {
    nameId: 'undefeated',
    name: 'Undefeated',
    description: 'Win 5 consecutive matches',
  },
  {
    nameId: 'social_butterfly',
    name: 'Social Butterfly',
    description: 'Add 5 friends',
  },
]

async function main() {
  console.log(`🚀 Iniciando seeding de la base de datos...`)

  try {
    // Solo sembrar si la base de datos está vacía (evita pisar datos reales).
    const userCount = await prisma.user.count()
    if (userCount > 0) {
      console.log('✨ La base de datos ya tiene datos, saltando seeding base.')
      return
    }

    console.log('👥 Creando usuarios...')
    const users: any[] = []
    for (const u of usersBase) {
      const user = await prisma.user.create({
        data: {
          username: u.username,
          email: u.email,
          passwordHash: await hashPassword(u.password),
          avatarUrl: u.avatarUrl,
          stats: {
            create: u.stats,
          },
        },
        include: { stats: true },
      })
      users.push(user)
      console.log(
        `   ✓ Usuario creado: ${user.username} - ELO: ${user.stats?.elo}`
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
      { userUsername: users[0].username, friendUsername: users[1].username },
      { userUsername: users[0].username, friendUsername: users[2].username },
      { userUsername: users[1].username, friendUsername: users[2].username },
      { userUsername: users[2].username, friendUsername: users[3].username },
      { userUsername: users[3].username, friendUsername: users[4].username },
    ]

    for (const friendship of friendships) {
      await prisma.friendship.create({
        data: friendship,
      })
      console.log(
        `   ✓ Amistad: ${friendship.userUsername} <-> ${friendship.friendUsername}`
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
        username: users[0].username,
        score: 2500,
        position: 1,
      },
      {
        matchId: createdMatches[0].id,
        username: users[1].username,
        score: 2100,
        position: 2,
      },
      {
        matchId: createdMatches[0].id,
        username: users[2].username,
        score: 1800,
        position: 3,
      },
      {
        matchId: createdMatches[0].id,
        username: users[3].username,
        score: 1500,
        position: 4,
      },
      {
        matchId: createdMatches[1].id,
        username: users[0].username,
        score: 3200,
        position: 1,
      },
      {
        matchId: createdMatches[1].id,
        username: users[2].username,
        score: 2100,
        position: 2,
      },
      { matchId: createdMatches[2].id, username: users[1].username, score: 1200 },
      { matchId: createdMatches[2].id, username: users[3].username, score: 950 },
      { matchId: createdMatches[2].id, username: users[4].username, score: 800 },
      { matchId: createdMatches[3].id, username: users[0].username, score: 0 },
      { matchId: createdMatches[3].id, username: users[1].username, score: 0 },
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
      { username: users[0].username, achievementNameId: achievements[0].nameId },
      { username: users[0].username, achievementNameId: achievements[1].nameId },
      { username: users[0].username, achievementNameId: achievements[2].nameId },
      { username: users[1].username, achievementNameId: achievements[0].nameId },
      { username: users[1].username, achievementNameId: achievements[1].nameId },
      { username: users[2].username, achievementNameId: achievements[0].nameId },
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

