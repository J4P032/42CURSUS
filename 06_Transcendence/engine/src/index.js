import express from 'express';
import cors from 'cors';
import { createDBHandler } from './dbhandler/client.js';
import { createPublisher } from './messaging/redisPublisher.js';
import { createRoomsRouter } from './routes/rooms.js';
import { createGamesRouter } from './routes/games.js';
import { createPlayersRouter } from './routes/players.js';

const app = express();
app.use(cors());
app.use(express.json());

const db = createDBHandler();
const publisher = createPublisher(process.env.REDIS_URL ?? null);

app.use(createRoomsRouter({ db, publisher }));
app.use(createGamesRouter({ db, publisher }));
app.use(createPlayersRouter({ db }));

const PORT = Number(process.env.PORT) || 3000;

try {
  await db.init();
} catch (err) {
  console.error('[engine] db.init() failed:', err.message);
}

app.listen(PORT, '0.0.0.0', () => {
});
