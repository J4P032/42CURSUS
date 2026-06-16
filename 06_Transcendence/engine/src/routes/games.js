import { Router } from 'express';
import Player from '@trascendence/shared/Player';
import { FACTIONS } from '@trascendence/shared/Factions';
import Gamestate from '../gameState.js';

export function createGamesRouter({ db, publisher }) {
  const router = Router();

  async function handleGameEnd(roomId, gameState) {
    if (gameState.statsPersisted) return;
    gameState.statsPersisted = true;
    try {
      await db.persistMatchEnd(gameState);
    } catch (err) {
      gameState.statsPersisted = false;
      console.error(`[engine] persistMatchEnd failed for ${roomId}:`, err.message);
    }
  }

  router.post('/rooms/:roomId/game/start', async (req, res) => {
    const room = await db.getRoom(req.params.roomId);
    if (!room) return res.status(404).json({ ok: false, error: 'Room not found' });
    try {
      const { factions } = req.body;
      const factionIds = factions || ['france', 'spain', 'england'];
      const players = factionIds.map((factionId, index) => {
        const faction = FACTIONS[factionId];
        if (!faction) throw new Error(`Faction ${factionId} not found`);
        return new Player({
          id: `player-${index + 1}`,
          name: faction.name,
          faction: factionId,
          color: faction.color,
        });
      });

      room.gameState = new Gamestate(players);
      await db.saveRoom(req.params.roomId, room);
      res.json({ ok: true, state: room.gameState.serialize() });
    } catch (err) {
      res.status(500).json({ ok: false, error: err.message });
    }
  });

  router.get('/rooms/:roomId/game/state', async (req, res) => {
    const room = await db.getRoom(req.params.roomId);
    if (!room?.gameState)
      return res.status(404).json({ ok: false, error: 'No game in progress' });
    res.json({ ok: true, state: room.gameState.serialize() });
  });

  router.post('/rooms/:roomId/game/reinforce', async (req, res) => {
    const room = await db.getRoom(req.params.roomId);
    if (!room?.gameState)
      return res.status(404).json({ ok: false, error: 'No game in progress' });

    const { territoryId } = req.body;
    const result = room.gameState.reinforce(territoryId);
    if (result.ok) {
      await db.saveRoom(req.params.roomId, room, { persist: false });
      publisher.publishState(req.params.roomId, room.gameState);
    }
    res.json(result);
  });

  router.post('/rooms/:roomId/game/attack', async (req, res) => {
    const room = await db.getRoom(req.params.roomId);
    if (!room?.gameState)
      return res.status(404).json({ ok: false, error: 'No game in progress' });

    const { attackFrom, attackTo, attackTroops } = req.body;
    const result = room.gameState.attack(attackFrom, attackTo, attackTroops);
    if (result.ok) {
      publisher.publishState(req.params.roomId, room.gameState);
      if (room.gameState.winner) {
        await handleGameEnd(req.params.roomId, room.gameState);
        await db.deleteRoom(req.params.roomId);
      } else {
        await db.saveRoom(req.params.roomId, room, { persist: false });
      }
    }
    res.json(result);
  });

  router.post('/rooms/:roomId/game/fortify', async (req, res) => {
    const room = await db.getRoom(req.params.roomId);
    if (!room?.gameState)
      return res.status(404).json({ ok: false, error: 'No game in progress' });

    const { fortifyFrom, fortifyTo, troops } = req.body;
    const result = room.gameState.fortify(fortifyFrom, fortifyTo, troops);
    if (result.ok) {
      await db.saveRoom(req.params.roomId, room, { persist: false });
      publisher.publishState(req.params.roomId, room.gameState);
    }
    res.json(result);
  });

  router.post('/rooms/:roomId/game/surrender', async (req, res) => {
    const room = await db.getRoom(req.params.roomId);
    if (!room?.gameState)
      return res.status(404).json({ ok: false, error: 'No game in progress' });

    const { playerId } = req.body;
    const result = await room.gameState.surrender(playerId);
    if (result.ok) {
      publisher.publishState(req.params.roomId, room.gameState);
      if (room.gameState.winner) {
        await handleGameEnd(req.params.roomId, room.gameState);
        await db.deleteRoom(req.params.roomId);
      } else {
        await db.saveRoom(req.params.roomId, room);
      }
    }
    res.json(result);
  });

  router.post('/rooms/:roomId/game/next-turn', async (req, res) => {
    const room = await db.getRoom(req.params.roomId);
    if (!room?.gameState)
      return res.status(404).json({ ok: false, error: 'No game in progress' });

    const result = await room.gameState.nextTurn();
    if (result.ok) {
      publisher.publishState(req.params.roomId, room.gameState);
      if (room.gameState.winner) {
        await handleGameEnd(req.params.roomId, room.gameState);
        await db.deleteRoom(req.params.roomId);
      } else {
        await db.saveRoom(req.params.roomId, room);
      }
    }
    res.json(result);
  });

  return router;
}
