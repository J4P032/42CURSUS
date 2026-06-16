export type ClientMsg =
  | { type: 'join'; roomId: string; playerId: string }
  | { type: 'leave' }
  | { type: 'chat'; text: string }
  | { type: 'ping' };

export type ServerMsg =
  | { type: 'joined'; roomId: string }
  | { type: 'state'; state: unknown }
  | { type: 'chat'; from: string; text: string; ts: number }
  | { type: 'error'; code: string; message: string }
  | { type: 'pong' };

export function parseClientMsg(raw: string): ClientMsg | null {
  let parsed: unknown;
  try {
    parsed = JSON.parse(raw);
  } catch {
    return null;
  }
  if (!parsed || typeof parsed !== 'object' || !('type' in parsed)) return null;
  const msg = parsed as { type: unknown; [k: string]: unknown };

  switch (msg.type) {
    case 'join':
      if (typeof msg.roomId !== 'string' || msg.roomId.trim() === '') return null;
      if (typeof msg.playerId !== 'string' || msg.playerId.trim() === '') return null;
      return { type: 'join', roomId: msg.roomId, playerId: msg.playerId };
    case 'leave':
      return { type: 'leave' };
    case 'chat':
      if (typeof msg.text !== 'string' || msg.text.length === 0) return null;
      return { type: 'chat', text: msg.text.slice(0, 1000) };
    case 'ping':
      return { type: 'ping' };
    default:
      return null;
  }
}
