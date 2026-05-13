import { Router } from 'express';

export function createPlayersRouter({ db }) {
  const router = Router();

  router.get('/rooms/:roomId/players/:id', async (req, res) => {
    const player = await db.getPlayer(req.params.id);
    if (!player) return res.status(404).json({ ok: false, error: 'Player not found' });
    res.json({ ok: true, player });
  });

  router.post('/matches', async (req, res) => {
    await db.saveMatchResult(req.body);
    res.json({ ok: true });
  });

  router.post('/players/:id/achievements', async (req, res) => {
    await db.unlockAchievement(req.params.id, req.body.achievementId);
    res.json({ ok: true });
  });

  return router;
}
