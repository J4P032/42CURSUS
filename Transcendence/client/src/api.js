const BASE_URL = `http://${window.location.hostname}:3000`;

export const wsUrl = () => `ws://${window.location.hostname}:42069`;

async function request(method, endpoint, body = null) {
  const options = {
    method,
    headers: { 'Content-Type': 'application/json' },
  };
  if (body) options.body = JSON.stringify(body);

  const res = await fetch(`${BASE_URL}${endpoint}`, options);
  return res.json();
}

export const api = {
  // Rooms
  createRoom:   (roomId, maxPlayers) => request('POST', '/rooms', { roomId, maxPlayers }),
  joinRoom:     (roomId, playerId, playerName, faction) => 
    request('POST', `/rooms/${roomId}/join`, { playerId, playerName, faction }),
  getRoom:      (roomId) => request('GET', `/rooms/${roomId}`),
  startRoom:    (roomId) => request('POST', `/rooms/${roomId}/start`),

  // Game
  getState:     (roomId) => request('GET', `/rooms/${roomId}/game/state`),
  reinforce:    (roomId, territoryId) => request('POST', `/rooms/${roomId}/game/reinforce`, { territoryId }),
  attack:       (roomId, attackFrom, attackTo, attackTroops) => 
    request('POST', `/rooms/${roomId}/game/attack`, { attackFrom, attackTo, attackTroops }),
  fortify:      (roomId, fortifyFrom, fortifyTo, troops) => 
    request('POST', `/rooms/${roomId}/game/fortify`, { fortifyFrom, fortifyTo, troops }),
  nextTurn:     (roomId) => request('POST', `/rooms/${roomId}/game/next-turn`),

  // Players
  getPlayer:          (roomId, id) => request('GET', `/rooms/${roomId}/players/${id}`),
  saveMatch:          (data) => request('POST', '/matches', data),
  unlockAchievement:  (playerId, achievementId) => 
    request('POST', `/players/${playerId}/achievements`, { achievementId }),
};