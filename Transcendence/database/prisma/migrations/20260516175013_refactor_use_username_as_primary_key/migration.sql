/*
  Warnings:

  - The primary key for the `friendships` table will be changed. If it partially fails, the table could be left without primary key constraint.
  - You are about to drop the column `friendId` on the `friendships` table. All the data in the column will be lost.
  - You are about to drop the column `userId` on the `friendships` table. All the data in the column will be lost.
  - You are about to drop the column `userId` on the `match_players` table. All the data in the column will be lost.
  - The primary key for the `stats` table will be changed. If it partially fails, the table could be left without primary key constraint.
  - You are about to drop the column `userId` on the `stats` table. All the data in the column will be lost.
  - The primary key for the `user_achievements` table will be changed. If it partially fails, the table could be left without primary key constraint.
  - You are about to drop the column `userusername` on the `user_achievements` table. All the data in the column will be lost.
  - The primary key for the `users` table will be changed. If it partially fails, the table could be left without primary key constraint.
  - You are about to drop the column `id` on the `users` table. All the data in the column will be lost.
  - A unique constraint covering the columns `[matchId,username]` on the table `match_players` will be added. If there are existing duplicate values, this will fail.
  - Added the required column `friendUsername` to the `friendships` table without a default value. This is not possible if the table is not empty.
  - Added the required column `userUsername` to the `friendships` table without a default value. This is not possible if the table is not empty.
  - Added the required column `username` to the `match_players` table without a default value. This is not possible if the table is not empty.
  - Added the required column `username` to the `stats` table without a default value. This is not possible if the table is not empty.
  - Added the required column `username` to the `user_achievements` table without a default value. This is not possible if the table is not empty.

*/
-- DropForeignKey
ALTER TABLE "friendships" DROP CONSTRAINT "friendships_friendId_fkey";

-- DropForeignKey
ALTER TABLE "friendships" DROP CONSTRAINT "friendships_userId_fkey";

-- DropForeignKey
ALTER TABLE "match_players" DROP CONSTRAINT "match_players_userId_fkey";

-- DropForeignKey
ALTER TABLE "stats" DROP CONSTRAINT "stats_userId_fkey";

-- DropForeignKey
ALTER TABLE "user_achievements" DROP CONSTRAINT "user_achievements_userusername_fkey";

-- DropIndex
DROP INDEX "match_players_matchId_userId_key";

-- AlterTable
ALTER TABLE "friendships" DROP CONSTRAINT "friendships_pkey",
DROP COLUMN "friendId",
DROP COLUMN "userId",
ADD COLUMN     "friendUsername" TEXT NOT NULL,
ADD COLUMN     "userUsername" TEXT NOT NULL,
ADD CONSTRAINT "friendships_pkey" PRIMARY KEY ("userUsername", "friendUsername");

-- AlterTable
ALTER TABLE "match_players" DROP COLUMN "userId",
ADD COLUMN     "username" VARCHAR(50) NOT NULL;

-- AlterTable
ALTER TABLE "stats" DROP CONSTRAINT "stats_pkey",
DROP COLUMN "userId",
ADD COLUMN     "username" VARCHAR(50) NOT NULL,
ADD CONSTRAINT "stats_pkey" PRIMARY KEY ("username");

-- AlterTable
ALTER TABLE "user_achievements" DROP CONSTRAINT "user_achievements_pkey",
DROP COLUMN "userusername",
ADD COLUMN     "username" VARCHAR(50) NOT NULL,
ADD CONSTRAINT "user_achievements_pkey" PRIMARY KEY ("username", "achievementName_id");

-- AlterTable
ALTER TABLE "users" DROP CONSTRAINT "users_pkey",
DROP COLUMN "id",
ADD CONSTRAINT "users_pkey" PRIMARY KEY ("username");

-- CreateIndex
CREATE UNIQUE INDEX "match_players_matchId_username_key" ON "match_players"("matchId", "username");

-- AddForeignKey
ALTER TABLE "friendships" ADD CONSTRAINT "friendships_userUsername_fkey" FOREIGN KEY ("userUsername") REFERENCES "users"("username") ON DELETE CASCADE ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "friendships" ADD CONSTRAINT "friendships_friendUsername_fkey" FOREIGN KEY ("friendUsername") REFERENCES "users"("username") ON DELETE CASCADE ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "match_players" ADD CONSTRAINT "match_players_username_fkey" FOREIGN KEY ("username") REFERENCES "users"("username") ON DELETE CASCADE ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "stats" ADD CONSTRAINT "stats_username_fkey" FOREIGN KEY ("username") REFERENCES "users"("username") ON DELETE CASCADE ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "user_achievements" ADD CONSTRAINT "user_achievements_username_fkey" FOREIGN KEY ("username") REFERENCES "users"("username") ON DELETE CASCADE ON UPDATE CASCADE;
