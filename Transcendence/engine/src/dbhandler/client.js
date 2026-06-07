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

export class InMemoryDBHandler {
  constructor() {
    this.rooms = new Map();
    this.players = new Map();
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

  async getPlayer(username) {
    return this.players.get(username) ?? null;
  }

  async saveMatchResult(matchData) {
    this.matches.push(matchData);
    console.log('Match result (in-memory):', matchData);
  }

  async unlockAchievement(username, achievementId) {
    const player = this.players.get(username);
    if (!player) return;
    if (!player.achievements.includes(achievementId)) {
      player.achievements.push(achievementId);
      console.log(`Achievement unlocked (in-memory): ${achievementId} for ${username}`);
    }
  }
}

export function createDBHandler() {
  // Future: pick implementation from env, e.g.
  //   if (process.env.DBHANDLER_URL) return new HttpDBHandler(process.env.DBHANDLER_URL);
  return new InMemoryDBHandler();
}
