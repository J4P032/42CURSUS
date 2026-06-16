-- CreateTable
CREATE TABLE "users" (
    "username" VARCHAR(50) NOT NULL,
    "email" VARCHAR(100) NOT NULL,
    "passwordHash" TEXT NOT NULL,
    "avatarUrl" TEXT,
    "createdAt" TIMESTAMP(6) NOT NULL DEFAULT CURRENT_TIMESTAMP,

    CONSTRAINT "users_pkey" PRIMARY KEY ("username")
);

-- CreateTable
CREATE TABLE "friendships" (
    "userUsername" TEXT NOT NULL,
    "friendUsername" TEXT NOT NULL,
    "createdAt" TIMESTAMP(6) NOT NULL DEFAULT CURRENT_TIMESTAMP,

    CONSTRAINT "friendships_pkey" PRIMARY KEY ("userUsername","friendUsername")
);

-- CreateTable
CREATE TABLE "matches" (
    "id" SERIAL NOT NULL,
    "gameMode" VARCHAR(50) NOT NULL,
    "maxPlayers" INTEGER NOT NULL DEFAULT 4,
    "status" VARCHAR(20) NOT NULL DEFAULT 'waiting',
    "gameState" JSONB,
    "createdAt" TIMESTAMP(6) NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "startedAt" TIMESTAMP(6),
    "endedAt" TIMESTAMP(6),

    CONSTRAINT "matches_pkey" PRIMARY KEY ("id")
);

-- CreateTable
CREATE TABLE "match_players" (
    "id" SERIAL NOT NULL,
    "matchId" INTEGER NOT NULL,
    "username" VARCHAR(50) NOT NULL,
    "score" INTEGER NOT NULL DEFAULT 0,
    "position" INTEGER,
    "joinedAt" TIMESTAMP(6) NOT NULL DEFAULT CURRENT_TIMESTAMP,

    CONSTRAINT "match_players_pkey" PRIMARY KEY ("id")
);

-- CreateTable
CREATE TABLE "stats" (
    "username" VARCHAR(50) NOT NULL,
    "gamesPlayed" INTEGER NOT NULL DEFAULT 0,
    "wins" INTEGER NOT NULL DEFAULT 0,
    "losses" INTEGER NOT NULL DEFAULT 0,
    "elo" INTEGER NOT NULL DEFAULT 1000,
    "territoriesConquered" INTEGER NOT NULL DEFAULT 0,
    "totalTurns" INTEGER NOT NULL DEFAULT 0,

    CONSTRAINT "stats_pkey" PRIMARY KEY ("username")
);

-- CreateTable
CREATE TABLE "rooms" (
    "roomId" VARCHAR(50) NOT NULL,
    "maxPlayers" INTEGER NOT NULL DEFAULT 4,
    "maxTurns" INTEGER NOT NULL DEFAULT 100,
    "started" BOOLEAN NOT NULL DEFAULT false,
    "players" JSONB NOT NULL DEFAULT '[]',
    "gameState" JSONB,
    "createdAt" TIMESTAMP(6) NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "updatedAt" TIMESTAMP(6) NOT NULL,

    CONSTRAINT "rooms_pkey" PRIMARY KEY ("roomId")
);

-- CreateTable
CREATE TABLE "achievements" (
    "id" SERIAL NOT NULL,
    "nameId" VARCHAR(50) NOT NULL,
    "name" VARCHAR(100) NOT NULL,
    "description" TEXT NOT NULL,

    CONSTRAINT "achievements_pkey" PRIMARY KEY ("id")
);

-- CreateTable
CREATE TABLE "user_achievements" (
    "username" VARCHAR(50) NOT NULL,
    "achievementNameId" VARCHAR(50) NOT NULL,
    "unlockedAt" TIMESTAMP(6) NOT NULL DEFAULT CURRENT_TIMESTAMP,

    CONSTRAINT "user_achievements_pkey" PRIMARY KEY ("username","achievementNameId")
);

-- CreateIndex
CREATE UNIQUE INDEX "users_username_key" ON "users"("username");

-- CreateIndex
CREATE UNIQUE INDEX "users_email_key" ON "users"("email");

-- CreateIndex
CREATE INDEX "friendships_friendUsername_idx" ON "friendships"("friendUsername");

-- CreateIndex
CREATE INDEX "match_players_matchId_idx" ON "match_players"("matchId");

-- CreateIndex
CREATE INDEX "match_players_username_idx" ON "match_players"("username");

-- CreateIndex
CREATE UNIQUE INDEX "match_players_matchId_username_key" ON "match_players"("matchId", "username");

-- CreateIndex
CREATE UNIQUE INDEX "achievements_nameId_key" ON "achievements"("nameId");

-- CreateIndex
CREATE INDEX "user_achievements_achievementNameId_idx" ON "user_achievements"("achievementNameId");

-- AddForeignKey
ALTER TABLE "friendships" ADD CONSTRAINT "friendships_userUsername_fkey" FOREIGN KEY ("userUsername") REFERENCES "users"("username") ON DELETE CASCADE ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "friendships" ADD CONSTRAINT "friendships_friendUsername_fkey" FOREIGN KEY ("friendUsername") REFERENCES "users"("username") ON DELETE CASCADE ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "match_players" ADD CONSTRAINT "match_players_matchId_fkey" FOREIGN KEY ("matchId") REFERENCES "matches"("id") ON DELETE CASCADE ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "match_players" ADD CONSTRAINT "match_players_username_fkey" FOREIGN KEY ("username") REFERENCES "users"("username") ON DELETE CASCADE ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "stats" ADD CONSTRAINT "stats_username_fkey" FOREIGN KEY ("username") REFERENCES "users"("username") ON DELETE CASCADE ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "user_achievements" ADD CONSTRAINT "user_achievements_username_fkey" FOREIGN KEY ("username") REFERENCES "users"("username") ON DELETE CASCADE ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "user_achievements" ADD CONSTRAINT "user_achievements_achievementNameId_fkey" FOREIGN KEY ("achievementNameId") REFERENCES "achievements"("nameId") ON DELETE CASCADE ON UPDATE CASCADE;
