import { FACTIONS, NEUTRAL_TERRITORIES } from '@trascendence/shared/Factions';
import { createScaledTerritories } from '@trascendence/shared/Territories';
import { checkCapitalVictory, getScoreWinner } from '@trascendence/shared/Victory';
import TurnManager from '@trascendence/shared/TurnManager';

const CANVAS_WIDTH = 1100;
const CANVAS_HEIGHT = 700;
const TERRITORIES = createScaledTerritories(CANVAS_WIDTH, CANVAS_HEIGHT);

export default class Gamestate {
  constructor(players, maxTurns = 100) {
	this.players = players;
	this.maxTurns = maxTurns;
	this.turn = 1;
	this.tm = new TurnManager(players);
	this.phase = this.tm.phase ?? TurnManager.PHASES.REINFORCE;
	this.winner = null;
	this.activeFactions = players.map((p) => p.faction);
	this.statsPersisted = false;
	this.territoryOwners = this._initTerritoryOwners();
	this.troopCount = this._initTroopCount();
	this.currentPlayer = this.tm.getCurrentPlayer();
	this.reinforcementsLeft = this._calculateReinforcements(this.currentPlayer.faction);
	this.territoriesAttackedThisTurn = new Set();
	
	// ========== PLAYER STATS ==========
	this.playerStats = {};
	players.forEach(player => {
	this.playerStats[player.id] = {
		faction: player.faction,
		territoriesConquered: 0,
		territoriesConquered_ids: [],
		gamesPlayed: 0,
		gamesWon: 0,
		totalTurns: 0,
		wonByScore: false,
		wonByCapitals: false,
	};
	});
  }

  _initTerritoryOwners() {
	const owners = {};
	Object.entries(FACTIONS).forEach(([factionId, faction]) => {
	  faction.territories.forEach((id) => {
		owners[id] = factionId;
	  });
	});
	NEUTRAL_TERRITORIES.forEach((id) => {
	  owners[id] = null;
	});
	return owners;
  }

  _initTroopCount() {
	const counts = {};
	Object.keys(TERRITORIES)
	  .filter((id) => !TERRITORIES[id].impassable)
	  .forEach((id) => {
		counts[id] = TERRITORIES[id].isRegCapital ? 3 : 2;
	  });
	return counts;
  }

  _calculateReinforcements(factionId) {
	const owned = Object.entries(this.territoryOwners)
	  .filter(([, owner]) => owner === factionId)
	  .map(([id]) => id);
	return Math.max(3, Math.floor(owned.length / 3));
  }

  serialize() {
	return {
	  currentPlayer: this.currentPlayer,
	  phase: this.phase,
	  turn: this.turn,
	  winner: this.winner,
	  territoryOwners: this.territoryOwners,
	  troopCount: this.troopCount,
	  reinforcementsLeft: this.reinforcementsLeft,
	  activeFactions: this.activeFactions,
	  statsPersisted: this.statsPersisted,
		playerStats: this.playerStats,
	  // Persistence-only fields (clients ignore unknown fields):
	  players: this.players,
	  maxTurns: this.maxTurns,
	  currentPlayerIndex: this.tm?.currentPlayer ?? 0,
	};
  }

  // Rehydrate from a serialized snapshot without re-running the constructor's
  // initialization (which would reset territory owners and troop counts).
  static fromSerialized(data) {
	const gs = Object.create(Gamestate.prototype);
	gs.players = data.players ?? [];
	gs.maxTurns = data.maxTurns ?? 100;
	gs.turn = data.turn ?? 1;
	gs.phase = data.phase ?? TurnManager.PHASES.REINFORCE;
	gs.winner = data.winner ?? null;
	gs.activeFactions = data.activeFactions ?? gs.players.map((p) => p.faction);
	gs.statsPersisted = data.statsPersisted ?? false;
	gs.territoryOwners = data.territoryOwners ?? {};
	gs.troopCount = data.troopCount ?? {};
	gs.reinforcementsLeft = data.reinforcementsLeft ?? 0;
	gs.playerStats = data.playerStats ?? {};
	gs.currentPlayer = data.currentPlayer ?? null;
	// territoriesAttackedThisTurn is a Set and is intentionally NOT persisted.
	// Restoring it as empty means a player whose turn was mid-attack at crash
	// time keeps the territory-level "attacked once" restriction until next turn,
	// which is acceptable for lifecycle-only persistence.
	gs.territoriesAttackedThisTurn = new Set();
	gs.tm = new TurnManager(gs.players);
	gs.tm.setCurrentPlayer(data.currentPlayerIndex ?? 0);
	gs.tm.phase = gs.phase;
	return gs;
  }

  reinforce(territoryId) {
	if (this.phase !== TurnManager.PHASES.REINFORCE)
	  return { ok: false, error: 'Not in reinforcement phase' };
	if (this.territoryOwners[territoryId] !== this.currentPlayer.faction)
	  return { ok: false, error: 'Can only reinforce owned territories' };
	if (this.reinforcementsLeft <= 0) return { ok: false, error: 'No reinforcements left' };

	this.troopCount[territoryId]++;
	this.reinforcementsLeft--;
	return { ok: true, state: this.serialize() };
  }

  attack(attackFrom, attackTo, attackTroops) {
	if (this.phase !== TurnManager.PHASES.ATTACK)
	  return { ok: false, error: 'Not in attack phase' };
	if (this.territoryOwners[attackFrom] !== this.currentPlayer.faction)
	  return { ok: false, error: 'Not your territory' };
	if (this.territoryOwners[attackTo] === this.currentPlayer.faction)
	  return { ok: false, error: 'Cannot attack own territories' };
	if (!TERRITORIES[attackFrom].neighbors.includes(attackTo))
	  return { ok: false, error: 'Can only attack neighboring territories' };
	if (this.troopCount[attackFrom] <= 1)
	  return { ok: false, error: 'Not enough troops to attack' };
	if (this.territoriesAttackedThisTurn.has(attackFrom))
	  return { ok: false, error: 'Territory has already attacked this turn' };

	const defenderTroops = Math.min(3, this.troopCount[attackTo]);
	const { attackerLosses, defenderLosses, attackDice, defenseDice, troopBonus } =
	  TurnManager.resolveCombat(attackTroops, defenderTroops);

	this.troopCount[attackFrom] -= attackerLosses;
	this.troopCount[attackTo] -= defenderLosses;

	let conquered = false;
	if (this.troopCount[attackTo] <= 0) {
	  const survivors = attackTroops - attackerLosses;
	  this.troopCount[attackTo] = survivors;
	  this.troopCount[attackFrom] -= survivors;
	  this.territoryOwners[attackTo] = this.currentPlayer.faction;
		conquered = true;

		// Actualiza stats del jugador atacante
		const attackerId = this.currentPlayer.id;
		this.playerStats[attackerId].territoriesConquered++;
		if (!this.playerStats[attackerId].territoriesConquered_ids.includes(attackTo)) {
			this.playerStats[attackerId].territoriesConquered_ids.push(attackTo);
		}

		this._handleEliminations();
	}

	this.territoriesAttackedThisTurn.add(attackFrom);

	return {
	  ok: true,
	  battleReport: {
		attackFrom,
		attackTo,
		attackerTroops: attackTroops,
		defenderTroops,
		attackDice,
		defenseDice,
		attackerLosses,
		defenderLosses,
		troopBonus,
		conquered,
	  },
	  state: this.serialize(),
	};
  }

  fortify(fortifyFrom, fortifyTo, troops) {
	if (this.phase !== TurnManager.PHASES.FORTIFY)
	  return { ok: false, error: 'Not in fortification phase' };
	if (this.territoryOwners[fortifyFrom] !== this.currentPlayer.faction)
	  return { ok: false, error: 'Not your territory' };
	if (this.territoryOwners[fortifyTo] !== this.currentPlayer.faction)
	  return { ok: false, error: 'Can only fortify between owned territories' };
	if (!TERRITORIES[fortifyFrom].neighbors.includes(fortifyTo))
	  return { ok: false, error: 'Can only fortify neighboring territories' };
	if (this.troopCount[fortifyFrom] - troops < 1)
	  return { ok: false, error: 'Not enough troops to fortify' };

	this.troopCount[fortifyFrom] -= troops;
	this.troopCount[fortifyTo] += troops;

	return { ok: true, state: this.serialize() };
  }

  _handleEliminations() {
	const eliminated = this.activeFactions.filter(
	  (fId) => this.territoryOwners[FACTIONS[fId].capital] !== fId
	);
	if (eliminated.length > 0) {
	  this.activeFactions = this.activeFactions.filter((f) => !eliminated.includes(f));
	}

	if (this.winner) return;
	const capitalWinner = this.activeFactions.find((fId) =>
	  checkCapitalVictory(fId, this.territoryOwners, this.activeFactions)
	);
	if (capitalWinner) {
	  this.winner = { factionId: capitalWinner, reason: 'capitals' };
	  const winnerId = this.players.find((p) => p.faction === capitalWinner)?.id;
	  if (winnerId) {
		this.playerStats[winnerId].gamesWon++;
		this.playerStats[winnerId].wonByCapitals = true;
	  }
	}
  }

  async surrender(playerId) {
	if (this.winner) return { ok: false, error: 'Game already ended' };
	const player = this.players.find((p) => p.id === playerId);
	if (!player) return { ok: false, error: 'Player not found' };
	if (!this.activeFactions.includes(player.faction)) {
	  return { ok: false, error: 'Player already eliminated' };
	}

	this.activeFactions = this.activeFactions.filter((f) => f !== player.faction);
	this._handleEliminations();

	if (!this.winner && this.currentPlayer?.id === playerId) {
	  let guard = 0;
	  while (!this.winner && this.currentPlayer?.id === playerId && guard++ < 12) {
		const result = await this.nextTurn();
		if (!result.ok) break;
	  }
	}

	return { ok: true, state: this.serialize() };
  }

  async nextTurn() {
	if (this.winner) return { ok: false, error: 'Game already ended' };

	await this.tm.nextTurn();

	while (
	  this.tm.phase === TurnManager.PHASES.REINFORCE &&
	  this.activeFactions.length > 0 &&
	  !this.activeFactions.includes(this.tm.getCurrentPlayer().faction)
	) {
	  await this.tm.nextTurn(); // REINFORCE -> ATTACK
	  await this.tm.nextTurn(); // ATTACK -> FORTIFY
	  await this.tm.nextTurn(); // FORTIFY -> next player's REINFORCE
	}

	this.currentPlayer = this.tm.getCurrentPlayer();
	this.phase = this.tm.phase;
	this.territoriesAttackedThisTurn = new Set();

	if (this.phase === TurnManager.PHASES.REINFORCE) {
	  this.turn++;
	  this.reinforcementsLeft = this._calculateReinforcements(this.currentPlayer.faction);

	  const capitalWinner = this.activeFactions.find((fId) =>
		checkCapitalVictory(fId, this.territoryOwners, this.activeFactions)
	  );
		if (capitalWinner) {
			this.winner = { factionId: capitalWinner, reason: 'capitals' };
			// Actualiza stats del ganador
			const winnerId = this.players.find(p => p.faction === capitalWinner)?.id;
			if (winnerId) {
				this.playerStats[winnerId].gamesWon++;
				this.playerStats[winnerId].wonByCapitals = true;
			}
		} else if (this.turn > this.maxTurns) {
			const scoreWinner = getScoreWinner(this.territoryOwners, this.activeFactions);
			this.winner = { factionId: scoreWinner, reason: 'score' };
			const winnerId = this.players.find(p => p.faction === scoreWinner)?.id;
			if (winnerId) {
				this.playerStats[winnerId].gamesWon++;
				this.playerStats[winnerId].wonByScore = true;
			}
		}

		// Incrementa turnos para el jugador actual
		this.playerStats[this.currentPlayer.id].totalTurns++;
	}

	return { ok: true, state: this.serialize() };
  }
}
