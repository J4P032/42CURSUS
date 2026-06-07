/*
  Warnings:

  - You are about to drop the column `name_id` on the `achievements` table. All the data in the column will be lost.
  - The primary key for the `user_achievements` table will be changed. If it partially fails, the table could be left without primary key constraint.
  - You are about to drop the column `achievementName_id` on the `user_achievements` table. All the data in the column will be lost.
  - A unique constraint covering the columns `[nameId]` on the table `achievements` will be added. If there are existing duplicate values, this will fail.
  - Added the required column `nameId` to the `achievements` table without a default value. This is not possible if the table is not empty.
  - Added the required column `achievementNameId` to the `user_achievements` table without a default value. This is not possible if the table is not empty.
  - Made the column `passwordHash` on table `users` required. This step will fail if there are existing NULL values in that column.

*/
-- DropForeignKey
ALTER TABLE "user_achievements" DROP CONSTRAINT "user_achievements_achievementName_id_fkey";

-- DropIndex
DROP INDEX "achievements_name_id_key";

-- AlterTable
ALTER TABLE "achievements" DROP COLUMN "name_id",
ADD COLUMN     "nameId" VARCHAR(50) NOT NULL;

-- AlterTable
ALTER TABLE "user_achievements" DROP CONSTRAINT "user_achievements_pkey",
DROP COLUMN "achievementName_id",
ADD COLUMN     "achievementNameId" VARCHAR(50) NOT NULL,
ADD CONSTRAINT "user_achievements_pkey" PRIMARY KEY ("username", "achievementNameId");

-- AlterTable
ALTER TABLE "users" ALTER COLUMN "passwordHash" SET NOT NULL;

-- CreateIndex
CREATE UNIQUE INDEX "achievements_nameId_key" ON "achievements"("nameId");

-- CreateIndex
CREATE INDEX "friendships_friendUsername_idx" ON "friendships"("friendUsername");

-- CreateIndex
CREATE INDEX "match_players_matchId_idx" ON "match_players"("matchId");

-- CreateIndex
CREATE INDEX "match_players_username_idx" ON "match_players"("username");

-- CreateIndex
CREATE INDEX "user_achievements_achievementNameId_idx" ON "user_achievements"("achievementNameId");

-- AddForeignKey
ALTER TABLE "user_achievements" ADD CONSTRAINT "user_achievements_achievementNameId_fkey" FOREIGN KEY ("achievementNameId") REFERENCES "achievements"("nameId") ON DELETE CASCADE ON UPDATE CASCADE;
