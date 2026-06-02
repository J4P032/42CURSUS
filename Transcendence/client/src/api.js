const BASE_URL = `http://${window.location.hostname}:3000`;
const DB_URL = `http://${window.location.hostname}:${import.meta.env.VITE_PRISMA_PORT || 4387}`;

export const wsUrl = () => `ws://${window.location.hostname}:42069`;

async function request(method, endpoint, body = null, useDb = false) {
  const options = {
    method,
    headers: { 'Content-Type': 'application/json' },
  };
  if (body) options.body = JSON.stringify(body);

  const url = useDb ? `${DB_URL}${endpoint}` : `${BASE_URL}${endpoint}`;
  const res = await fetch(url, options);
  return res.json();
}

export const api = {
  // Auth (Usan useDb = true)
  login: (email, password) => request('POST', '/auth/login', { email, password }, true),
  register: (email, username, password) => request('POST', '/auth/register', { email, username, password }, true),

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
  getPlayer: (userId) => request('GET', `/users/${userId}`, null, true),
  //saveMatch: (data) => request('POST', '/matches', data, true),
  saveMatch:          (data) => request('POST', '/matches', data, true),
  unlockAchievement: (userId, achievementId) => 
    request('POST', `/users/${userId}/achievements/${achievementId}`, null, true),
 // unlockAchievement:  (playerId, achievementId) => 
 //   request('POST', `/players/${playerId}/achievements`, { achievementId }),
};
