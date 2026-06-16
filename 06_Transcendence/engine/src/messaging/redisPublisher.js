import Redis from 'ioredis';

export function createPublisher(redisUrl) {
  if (!redisUrl) {
    console.warn('[redis] REDIS_URL not set — game state will not be broadcast');
    return { publishState: () => {} };
  }

  const client = new Redis(redisUrl, { maxRetriesPerRequest: null, lazyConnect: false });
  client.on('error', (err) => console.error('[redis] publisher error:', err.message));

  return {
    publishState(roomId, gameState) {
      if (!gameState) return;
      try {
        client.publish(`game:${roomId}:state`, JSON.stringify(gameState.serialize()));
      } catch (err) {
        console.error(`[redis] publish failed for room=${roomId}:`, err.message);
      }
    },
  };
}
