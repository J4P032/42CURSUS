import { RoomRegistry } from './rooms.js';
import { startRedisSubscriber } from './redisSubscriber.js';
import { startWsServer } from './wsServer.js';

const PORT = Number(process.env.PORT ?? 42069);
const REDIS_URL = process.env.REDIS_URL ?? 'redis://localhost:6379';

const rooms = new RoomRegistry();
const sub = startRedisSubscriber(REDIS_URL, rooms);
const wss = startWsServer(PORT, rooms);

console.log(`realtime starting — port=${PORT}, redis=${REDIS_URL}`);

function shutdown(signal: string): void {
  console.log(`\n[realtime] received ${signal}, shutting down`);
  wss.close(() => {
    sub.disconnect();
    process.exit(0);
  });
  // hard-exit after 5s if close hangs
  setTimeout(() => process.exit(1), 5_000).unref();
}

process.on('SIGINT', () => shutdown('SIGINT'));
process.on('SIGTERM', () => shutdown('SIGTERM'));

process.on('SIGUSR2', () => {
  console.log(
    `[realtime] memory=${JSON.stringify(process.memoryUsage())} rooms=${rooms.totalConnections()} conns`,
  );
});
