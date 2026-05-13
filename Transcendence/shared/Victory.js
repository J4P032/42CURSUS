import { TERRITORIES } from './Territories.js';
import { FACTIONS } from './Factions.js';

/**
 * Calculates the score for a faction based on territories owned.
 * @param {string} factionId
 * @param {Object} territoryOwners
 * @returns {number}
 */
export function calculateScore(factionId, territoryOwners) {
  let score = 0;
  Object.entries(territoryOwners).forEach(([territoryId, owner]) => {
    if (owner !== factionId) return;
    const territory = TERRITORIES[territoryId];
    if (!territory) return;

    // Enemy capital conquered — 3 points
    const isEnemyCapital = Object.entries(FACTIONS).some(
      ([fId, faction]) => fId !== factionId && faction.capital === territoryId
    );
    if (isEnemyCapital) {
      score += 3;
      return;
    }

    // Regional capital conquered — 2 points
    if (territory.isRegCapital) {
      score += 2;
      return;
    }

    // Normal territory conquered — 1 point
    score += 1;
  });
  return score;
}

/**
 * Checks if a faction has won by capturing all enemy faction capitals.
 * @param {string} factionId
 * @param {Object} territoryOwners
 * @param {string[]} activeFactions - faction ids currently playing
 * @returns {boolean}
 */
export function checkCapitalVictory(factionId, territoryOwners, activeFactions) {
  return activeFactions
    .filter((id) => id !== factionId)
    .every((enemyId) => territoryOwners[FACTIONS[enemyId].capital] === factionId);
}

/**
 * Returns the winner by score at the end of max turns.
 * @param {Object} territoryOwners
 * @param {string[]} activeFactions
 * @returns {string} factionId of the winner
 */
export function getScoreWinner(territoryOwners, activeFactions) {
  return activeFactions.reduce((best, factionId) => {
    const score = calculateScore(factionId, territoryOwners);
    const bestScore = calculateScore(best, territoryOwners);
    return score > bestScore ? factionId : best;
  });
}
