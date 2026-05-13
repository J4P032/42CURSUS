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
    console.log(`[redis] connected to ${redisUrl}`);
  });
  sub.on('error', (err) => {
    console.error('[redis] error:', err.message);
  });

  sub.psubscribe(CHANNEL_PATTERN, (err, count) => {
    if (err) {
      console.error('[redis] psubscribe failed:', err.message);
      return;
    }
    console.log(`[redis] psubscribed to '${CHANNEL_PATTERN}' (count=${count})`);
  });

  sub.on('pmessage', (_pattern, channel, message) => {
    const m = CHANNEL_RE.exec(channel);
    if (!m) return;
    const roomId = m[1];
    let state: unknown;
    try {
      state = JSON.parse(message);
    } catch (e) {
      console.error(`[redis] invalid JSON on ${channel}:`, (e as Error).message);
      return;
    }
    rooms.broadcast(roomId, { type: 'state', state });
  });

  return sub;
}
