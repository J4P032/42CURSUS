import type { WebSocket } from 'ws';
import type { RoomRegistry } from './rooms.js';

export function handleChat(ws: WebSocket, text: string, rooms: RoomRegistry): void {
  const meta = rooms.metaOf(ws);
  if (!meta) {
    ws.send(
      JSON.stringify({ type: 'error', code: 'not_joined', message: 'Join a room first' }),
    );
    return;
  }
  rooms.broadcast(meta.roomId, {
    type: 'chat',
    from: meta.playerId,
    text,
    ts: Date.now(),
  });
}
