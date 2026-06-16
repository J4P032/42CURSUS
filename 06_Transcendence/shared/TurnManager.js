import Player from './Player.js';

/**
 * Manages turn-based game logic, including player turns, phases, and dice rolls.
 *
 * @class TurnManager
 */

export default class TurnManager {
  constructor(players = []) {
    this.players = players;
    this.currentPlayer = 0;
    this.phase = TurnManager.PHASES.REINFORCE;
  }
  /**
   * Enum for game phases.
   * @readonly
   * @enum {string}
   */
  static PHASES = {
    REINFORCE: 'Reinforce',
    ATTACK: 'Attack',
    FORTIFY: 'Fortify',
    WON: 'Won',
  };

  /**
   * Sets the list of players for the game.
   *
   * @param {Array} players - An array of player objects to set. Defaults to an empty array.
   */
  setPlayers(players = []) {
    this.players = players;
  }

  /**
   * Sets the current player by their index.
   *
   * @param {number} index - The index of the player to set as the current player.
   */
  setCurrentPlayer(index) {
    this.currentPlayer = index;
  }

  /**
   * Returns the current player object from the players array.
   * If the players array is invalid or empty, returns null.
   *
   * @returns {Object|null} The current player object, or null if not available.
   */
  getCurrentPlayer() {
    if (!Array.isArray(this.players) || this.players.length === 0) return null;
    return this.players[this.currentPlayer] ?? null;
  }

  /**
   * Maximum number of units allowed for attack.
   * Maximum number of units allowed for defense.
   * @type {number}
   * @readonly
   */
  static MAX_ATTACK_UNITS = 3;
  static MAX_DEFENSE_UNITS = 3;

  /**
   * Returns the index of the next player.
   *
   * @param {number} currentPlayer - The index of the current player.
   * @returns {number} The index of the next player.
   */
  static nextPlayer(currentPlayer, totalPlayers) {
    return (currentPlayer + 1) % totalPlayers;
  }

  /**
   * Rolls a specified number of dice and returns the results sorted descending.
   *
   * @param {number} count - Number of dice to roll.
   * @returns {number[]} Array of dice results sorted from highest to lowest.
   */
  static rollDice(count) {
    return Array.from({ length: count }, () => Math.ceil(Math.random() * 6)).sort((a, b) => b - a);
  }

  /**
   * Returns the next phase in the game cycle.
   *
   * @param {string} phase - The current phase.
   * @returns {string} The next phase.
   */
  static nextPhase(phase) {
    if (phase === TurnManager.PHASES.REINFORCE) return TurnManager.PHASES.ATTACK;
    if (phase === TurnManager.PHASES.ATTACK) return TurnManager.PHASES.FORTIFY;
    if (phase === TurnManager.PHASES.FORTIFY) return TurnManager.PHASES.REINFORCE;
    return TurnManager.PHASES.REINFORCE;
  }

  /**
   * Advances the game to the next turn, confirming the current player's turn,
   * updating the current player if in the FORTIFY phase, and progressing to the next phase.
   *
   * @async
   * @returns {Player} The player whose turn is now active.
   */
  async nextTurn() {
    await confirmTurn(this.getCurrentPlayer().id);

    if (this.phase === TurnManager.PHASES.FORTIFY) {
      this.currentPlayer = TurnManager.nextPlayer(this.currentPlayer, this.players.length);
    }
    this.phase = TurnManager.nextPhase(this.phase);

    return this.getCurrentPlayer();
  }

  /**
   * Resolves combat between attacker and defender troops.
   * @param {number} attackerTroops - The number of troops attacking.
   * @param {number} defenderTroops - The number of troops defending.
   * @returns {Object} The result of the combat resolution.
   */
  static resolveCombat(attackerTroops, defenderTroops) {
    const diceCount = Math.min(attackerTroops, defenderTroops);
    const troopBonus = Math.max(0, attackerTroops - defenderTroops);
    const attackDice = TurnManager.rollDice(diceCount);
    const defenseDice = TurnManager.rollDice(diceCount);
    for (let i = 0; i < attackDice.length; i++) {
      attackDice[i] += troopBonus;
    }

    let attackerLosses = 0;
    let defenderLosses = 0;

    for (let i = 0; i < diceCount; i++) {
      if (attackDice[i] > defenseDice[i]) {
        defenderLosses++;
      } else {
        attackerLosses++;
      }
    }
    return { attackerLosses, defenderLosses, attackDice, defenseDice, troopBonus };
  }
}

/**
 * Confirms a player's turn asynchronously.
 *
 * @param {string|number} playerId - The unique identifier of the player whose turn is being confirmed.
 * @returns {Promise<{playerId: string|number, confirmed: boolean}>} A promise that resolves to an object indicating the player's ID and confirmation status.
 */
function confirmTurn(playerId) {
  return new Promise((resolve) => {
    setTimeout(() => resolve({ playerId, confirmed: true }), 300);
  });
}
