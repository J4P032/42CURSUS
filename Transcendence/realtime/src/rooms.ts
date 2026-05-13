import type { WebSocket } from 'ws';
import type { ServerMsg } from './protocol.js';

export interface ConnectionMeta {
  roomId: string;
  playerId: string;
}

export class RoomRegistry {
  private rooms = new Map<string, Set<WebSocket>>();
  private meta = new WeakMap<WebSocket, ConnectionMeta>();

  join(roomId: string, playerId: string, ws: WebSocket): void {
    this.leave(ws);
    let set = this.rooms.get(roomId);
    if (!set) {
      set = new Set();
      this.rooms.set(roomId, set);
    }
    set.add(ws);
    this.meta.set(ws, { roomId, playerId });
  }

  leave(ws: WebSocket): void {
    const m = this.meta.get(ws);
    if (!m) return;
    const set = this.rooms.get(m.roomId);
    if (set) {
      set.delete(ws);
      if (set.size === 0) this.rooms.delete(m.roomId);
    }
    this.meta.delete(ws);
  }

  metaOf(ws: WebSocket): ConnectionMeta | undefined {
    return this.meta.get(ws);
  }

  broadcast(roomId: string, msg: ServerMsg, exclude?: WebSocket): void {
    const set = this.rooms.get(roomId);
    if (!set) return;
    const payload = JSON.stringify(msg);
    for (const ws of set) {
      if (ws === exclude) continue;
      if (ws.readyState !== ws.OPEN) continue;
      // Soft backpressure cap: 1 MB. Drop slow clients.
      if (ws.bufferedAmount > 1_000_000) {
        ws.terminate();
        continue;
      }
      ws.send(payload);
    }
  }

  size(roomId: string): number {
    return this.rooms.get(roomId)?.size ?? 0;
  }

  totalConnections(): number {
    let n = 0;
    for (const s of this.rooms.values()) n += s.size;
    return n;
  }
}
