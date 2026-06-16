import { Router } from 'express';
import Player from '@trascendence/shared/Player';
import { FACTIONS } from '@trascendence/shared/Factions';
import Gamestate from '../gameState.js';

export function createRoomsRouter({ db, publisher }) {
  const router = Router();

  router.get('/rooms', async (_req, res) => {
    const rooms = await db.listRooms();
    res.json({ ok: true, rooms });
  });

  router.post('/rooms', async (req, res) => {
    const { roomId, maxPlayers, maxTurns } = req.body;
    if (!roomId || roomId.trim() === '')
      return res.status(400).json({ ok: false, error: 'Invalid room name' });
    if (await db.hasRoom(roomId))
      return res.status(409).json({ ok: false, error: 'Room already exists' });

    const turns = Number.isInteger(maxTurns) ? maxTurns : 100;
    if (turns < 10 || turns > 500)
      return res.status(400).json({ ok: false, error: 'maxTurns must be between 10 and 500' });

    await db.saveRoom(roomId, {
      maxPlayers,
      maxTurns: turns,
      players: [],
      gameState: null,
      started: false,
    });
    res.json({ ok: true, roomId });
  });

  router.post('/rooms/:roomId/join', async (req, res) => {
    const room = await db.getRoom(req.params.roomId);
    if (!room) return res.status(404).json({ ok: false, error: 'Room not found' });
    if (room.started) return res.status(400).json({ ok: false, error: 'Game already started' });
    if (room.players.length >= room.maxPlayers)
      return res.status(400).json({ ok: false, error: 'Room is full' });

    const { playerId, playerName, faction } = req.body;
    if (room.players.some((p) => p.faction === faction))
      return res.status(400).json({ ok: false, error: 'Faction already taken' });
    if (room.players.some((p) => p.id === playerId))
      return res.status(400).json({ ok: false, error: 'Already in room' });

    room.players.push(
      new Player({ id: playerId, name: playerName, faction, color: FACTIONS[faction].color })
    );
    await db.saveRoom(req.params.roomId, room);
    res.json({
      ok: true,
      room: { players: room.players, maxPlayers: room.maxPlayers, started: room.started },
    });
  });

  router.get('/rooms/:roomId', async (req, res) => {
    const room = await db.getRoom(req.params.roomId);
    if (!room) return res.status(404).json({ ok: false, error: 'Room not found' });
    res.json({
      ok: true,
      room: { players: room.players, maxPlayers: room.maxPlayers, started: room.started },
    });
  });

  router.post('/rooms/:roomId/start', async (req, res) => {
    const room = await db.getRoom(req.params.roomId);
    if (!room) return res.status(404).json({ ok: false, error: 'Room not found' });
    if (room.players.length < 2)
      return res.status(400).json({ ok: false, error: 'Not enough players' });
    if (room.started) return res.status(400).json({ ok: false, error: 'Already started' });

    room.gameState = new Gamestate(room.players, room.maxTurns ?? 100);
    room.started = true;
    await db.saveRoom(req.params.roomId, room);
    publisher.publishState(req.params.roomId, room.gameState);
    res.json({ ok: true, state: room.gameState.serialize() });
  });

  return router;
}
