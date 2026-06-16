import { Redis } from 'ioredis';
import type { RoomRegistry } from './rooms.js';

const CHANNEL_PATTERN = 'game:*:state';
const CHANNEL_RE = /^game:([^:]+):state$/;

export function startRedisSubscriber(redisUrl: string, rooms: RoomRegistry): Redis {
  const sub = new Redis(redisUrl, {
    lazyConnect: false,
    maxRetriesPerRequest: null,
  });

  sub.on('connect', () => {
  });
  sub.on('error', (err) => {
  });

  sub.psubscribe(CHANNEL_PATTERN, (err, count) => {
    if (err) {
      return;
    }
  });

  sub.on('pmessage', (_pattern, channel, message) => {
    const m = CHANNEL_RE.exec(channel);
    if (!m) return;
    const roomId = m[1];
    let state: unknown;
    try {
      state = JSON.parse(message);
    } catch (e) {
      return;
    }
    rooms.broadcast(roomId, { type: 'state', state });
  });

  return sub;
}
