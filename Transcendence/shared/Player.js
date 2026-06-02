import { FACTIONS } from './Factions.js';

/**
 * Represents a player in the game.
 * @class
 *
 * @param {Object} params - Player parameters.
 * @param {string|number} params.id - Unique identifier for the player.
 * @param {string} params.name - Name of the player.
 * @param {string} params.color - Color associated with the player.
 */

export default class Player {
  constructor({ id, name, color, faction }) {
    this.id = id;
    this.name = name;
    this.color = color;
    this.faction = faction;
    this.troops = 0;
  }

  /**
   * Sets the number of troops for the player.
   * @param {number} amount - The number of troops to set. Must be >= 0.
   */
  setTroops(amount) {
    this.troops = Math.max(0, amount);
  }

  /**
   * Adds troops to the player's current troop count.
   * @param {number} amount - The number of troops to add. Must be >= 0.
   */

  addTroops(amount) {
    this.troops += Math.max(0, amount);
  }

  /**
   * Spends one troop if available.
   * @returns {boolean} True if a troop was spent, false otherwise.
   */
  spendTroop() {
    if (this.troops <= 0) return false;
    this.troops -= 1;
    return true;
  }
}

export const MAX_PLAYERS = 4;
