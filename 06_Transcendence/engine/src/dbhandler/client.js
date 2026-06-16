// DBHandler client — seam for the future Issue-#X DB Handler service.
// Routes only ever interact with the interface defined here, never with raw
// in-memory state.
//
// Two implementations:
//   - InMemoryDBHandler: ephemeral, dies with the engine process.
//   - HttpDBHandler:     persists rooms to the database service. Wraps an
//                        in-memory cache so reads return live Gamestate
//                        references (mutations during a turn are observed
//                        without extra fetches); writes flush to HTTP only
//                        on lifecycle events.
//
// Pick implementation by setting DBHANDLER_URL in the engine environment.

import Gamestate from '../gameState.js';
import { calculateScore } from '@trascendence/shared/Victory';

// Build the per-player records the DB needs from a finished Gamestate.
// Position 1 is the winner; remaining players are ranked by score descending.
function buildMatchPayload(gameState) {
  const { winner, players, territoryOwners, playerStats = {} } = gameState;
  const winnerFaction = winner?.factionId ?? null;
  const ranked = players
    .map((p) => {
      const stats = playerStats[p.id] ?? {};
      return {
        username: p.id,
        faction: p.faction,
        score: calculateScore(p.faction, territoryOwners),
        won: p.faction === winnerFaction,
        territoriesConquered: stats.territoriesConquered ?? 0,
        totalTurns: stats.totalTurns ?? 0,
      };
    })
    .sort((a, b) => {
      if (a.won !== b.won) return a.won ? -1 : 1;
      return b.score - a.score;
    })
    .map((entry, idx) => ({ ...entry, position: idx + 1 }));
  return ranked;
}

export class InMemoryDBHandler {
  constructor() {
    this.rooms = new Map();
    this.players = new Map();
    this.matches = [];
  }

  async init() {
    // nothing to restore
  }

  async getRoom(roomId) {
    return this.rooms.get(roomId) ?? null;
  }

  async hasRoom(roomId) {
    return this.rooms.has(roomId);
  }

  async listRooms() {
    return Array.from(this.rooms.entries()).map(([roomId, room]) => ({
      roomId,
      maxPlayers: room.maxPlayers,
      started: !!room.started,
      players: room.players ?? [],
    }));
  }

  async saveRoom(roomId, room /* , opts */) {
    this.rooms.set(roomId, room);
  }

  async deleteRoom(roomId) {
    this.rooms.delete(roomId);
  }

  async getPlayer(username) {
    return this.players.get(username) ?? null;
  }

  async saveMatchResult(matchData) {
    this.matches.push(matchData);
  }

  async persistMatchEnd(gameState) {
    // In-memory: just keep the record locally so tests/dev runs can inspect it.
    this.matches.push(buildMatchPayload(gameState));
  }

  async unlockAchievement(username, achievementId) {
    const player = this.players.get(username);
    if (!player) return;
    if (!player.achievements.includes(achievementId)) {
      player.achievements.push(achievementId);
    }
  }
}

// Persists rooms to the database service. Reads always hit the local cache,
// which holds the live Gamestate reference (so per-action mutations require
// no DB round-trip). Writes hit the DB only when the caller explicitly asks
// for persistence (opts.persist !== false), so mid-turn actions stay local
// while lifecycle events (create/join/start/next-turn) get flushed.
export class HttpDBHandler {
  constructor(baseUrl) {
    this.baseUrl = baseUrl.replace(/\/$/, '');
    this.rooms = new Map();
    this.players = new Map();
    this.matches = [];
  }

  async init() {
    const res = await fetch(`${this.baseUrl}/rooms`);
    if (!res.ok) {
      throw new Error(`Failed to load rooms from DB service: ${res.status}`);
    }
    const rows = await res.json();
    for (const row of rows) {
      const room = {
        maxPlayers: row.maxPlayers,
        maxTurns: row.maxTurns ?? 100,
        players: row.players ?? [],
        started: row.started ?? false,
        gameState: row.gameState ? Gamestate.fromSerialized(row.gameState) : null,
      };
      this.rooms.set(row.roomId, room);
    }
    console.log(`[engine] restored ${this.rooms.size} room(s) from DB`);
  }

  async getRoom(roomId) {
    return this.rooms.get(roomId) ?? null;
  }

  async hasRoom(roomId) {
    return this.rooms.has(roomId);
  }

  async listRooms() {
    return Array.from(this.rooms.entries()).map(([roomId, room]) => ({
      roomId,
      maxPlayers: room.maxPlayers,
      started: !!room.started,
      players: room.players ?? [],
    }));
  }

  async saveRoom(roomId, room, opts = {}) {
    this.rooms.set(roomId, room);
    if (opts.persist === false) return;

    const body = {
      maxPlayers: room.maxPlayers,
      maxTurns: room.maxTurns ?? 100,
      started: !!room.started,
      players: room.players ?? [],
      gameState: room.gameState ? room.gameState.serialize() : null,
    };
    const res = await fetch(`${this.baseUrl}/rooms/${encodeURIComponent(roomId)}`, {
      method: 'PUT',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify(body),
    });
    if (!res.ok) {
      console.error(`[engine] failed to persist room ${roomId}: HTTP ${res.status}`);
    }
  }

  async deleteRoom(roomId) {
    this.rooms.delete(roomId);
    const res = await fetch(`${this.baseUrl}/rooms/${encodeURIComponent(roomId)}`, {
      method: 'DELETE',
    });
    if (!res.ok && res.status !== 404) {
      console.error(`[engine] failed to delete room ${roomId}: HTTP ${res.status}`);
    }
  }

  async getPlayer(username) {
    return this.players.get(username) ?? null;
  }

  async saveMatchResult(matchData) {
    this.matches.push(matchData);
  }

  async persistMatchEnd(gameState) {
    const ranked = buildMatchPayload(gameState);
    let matchId = null;
    try {
      const matchRes = await fetch(`${this.baseUrl}/matches`, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({
          gameMode: 'great-risk',
          maxPlayers: ranked.length,
          status: 'completed',
          gameState: gameState.serialize(),
        }),
      });
      if (!matchRes.ok) {
        console.error(`[engine] failed to create match record: HTTP ${matchRes.status}`);
      } else {
        const match = await matchRes.json();
        matchId = match.id;
      }
    } catch (err) {
      console.error('[engine] error creating match record:', err.message);
    }

    await Promise.all(
      ranked.map(async (entry) => {
        if (matchId != null) {
          try {
            const res = await fetch(
              `${this.baseUrl}/matches/${matchId}/players/${encodeURIComponent(entry.username)}`,
              {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({ score: entry.score, position: entry.position }),
              }
            );
            if (!res.ok && res.status !== 400) {
              console.error(`[engine] failed to record match-player ${entry.username}: HTTP ${res.status}`);
            }
          } catch (err) {
            console.error(`[engine] error recording match-player ${entry.username}:`, err.message);
          }
        }

        try {
          const res = await fetch(
            `${this.baseUrl}/users/${encodeURIComponent(entry.username)}/stats/record-game`,
            {
              method: 'POST',
              headers: { 'Content-Type': 'application/json' },
              body: JSON.stringify({
                won: entry.won,
                territoriesConquered: entry.territoriesConquered,
                totalTurns: entry.totalTurns,
              }),
            }
          );
          if (!res.ok) {
            console.error(`[engine] failed to record stats for ${entry.username}: HTTP ${res.status}`);
          }
        } catch (err) {
          console.error(`[engine] error recording stats for ${entry.username}:`, err.message);
        }
      })
    );
  }

  async unlockAchievement(username, achievementId) {
    const player = this.players.get(username);
    if (!player) return;
    if (!player.achievements.includes(achievementId)) {
      player.achievements.push(achievementId);
    }
  }
}

export function createDBHandler() {
  if (process.env.DBHANDLER_URL) {
    return new HttpDBHandler(process.env.DBHANDLER_URL);
  }
  return new InMemoryDBHandler();
}
