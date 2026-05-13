// DBHandler client — seam for the future Issue-#X DB Handler service.
// Routes only ever interact with the interface defined here, never with raw
// in-memory state. To swap in a real DB Handler, implement the same async
// methods (e.g. an HttpDBHandler that fetches /rooms/:id) and return it from
// createDBHandler().
//
// Note: in-memory `getRoom` returns the live object reference, so Gamestate
// instance methods survive a get→mutate→save cycle. A real DB Handler that
// serializes over the wire will need to rehydrate Gamestate (e.g. via a
// `Gamestate.fromSerialized()` factory) before returning the room.

const SEED_PLAYERS = {
  'player-1': {
    id: 'player-1',
    name: 'Player 1',
    achievements: [],
    stats: { gamesPlayed: 0, gamesWon: 0, territoriesConquered: 0, totalTurns: 0 },
    matchHistory: [],
  },
  'player-2': {
    id: 'player-2',
    name: 'Player 2',
    achievements: [],
    stats: { gamesPlayed: 0, gamesWon: 0, territoriesConquered: 0, totalTurns: 0 },
    matchHistory: [],
  },
  'player-3': {
    id: 'player-3',
    name: 'Player 3',
    achievements: [],
    stats: { gamesPlayed: 0, gamesWon: 0, territoriesConquered: 0, totalTurns: 0 },
    matchHistory: [],
  },
};

export class InMemoryDBHandler {
  constructor() {
    this.rooms = new Map();
    this.players = new Map(
      Object.entries(SEED_PLAYERS).map(([id, p]) => [id, structuredClone(p)])
    );
    this.matches = [];
  }

  async getRoom(roomId) {
    return this.rooms.get(roomId) ?? null;
  }

  async hasRoom(roomId) {
    return this.rooms.has(roomId);
  }

  async saveRoom(roomId, room) {
    this.rooms.set(roomId, room);
  }

  async deleteRoom(roomId) {
    this.rooms.delete(roomId);
  }

  async getPlayer(playerId) {
    return this.players.get(playerId) ?? null;
  }

  async saveMatchResult(matchData) {
    this.matches.push(matchData);
    console.log('Match result (in-memory):', matchData);
  }

  async unlockAchievement(playerId, achievementId) {
    const player = this.players.get(playerId);
    if (!player) return;
    if (!player.achievements.includes(achievementId)) {
      player.achievements.push(achievementId);
      console.log(`Achievement unlocked (in-memory): ${achievementId} for ${playerId}`);
    }
  }
}

export function createDBHandler() {
  // Future: pick implementation from env, e.g.
  //   if (process.env.DBHANDLER_URL) return new HttpDBHandler(process.env.DBHANDLER_URL);
  return new InMemoryDBHandler();
}
