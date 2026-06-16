const BASE_URL = '/api/engine';
const DB_URL = '/api/db';

export const wsUrl = () => {
  const proto = window.location.protocol === 'https:' ? 'wss:' : 'ws:';
  return `${proto}//${window.location.host}/ws`;
};

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
  createRoom:   (roomId, maxPlayers, maxTurns) => request('POST', '/rooms', { roomId, maxPlayers, maxTurns }),
  joinRoom:     (roomId, playerId, playerName, faction) =>
    request('POST', `/rooms/${roomId}/join`, { playerId, playerName, faction }),
  getRoom:      (roomId) => request('GET', `/rooms/${roomId}`),
  listRooms:    () => request('GET', '/rooms'),
  startRoom:    (roomId) => request('POST', `/rooms/${roomId}/start`),

  // Game
  getState:     (roomId) => request('GET', `/rooms/${roomId}/game/state`),
  reinforce:    (roomId, territoryId) => request('POST', `/rooms/${roomId}/game/reinforce`, { territoryId }),
  attack:       (roomId, attackFrom, attackTo, attackTroops) =>
    request('POST', `/rooms/${roomId}/game/attack`, { attackFrom, attackTo, attackTroops }),
  fortify:      (roomId, fortifyFrom, fortifyTo, troops) =>
    request('POST', `/rooms/${roomId}/game/fortify`, { fortifyFrom, fortifyTo, troops }),
  nextTurn:     (roomId) => request('POST', `/rooms/${roomId}/game/next-turn`),
  surrender:    (roomId, playerId) =>
    request('POST', `/rooms/${roomId}/game/surrender`, { playerId }),

  // Players
  getPlayer: (username) => request('GET', `/users/${username}`, null, true),
  updateUser: (username, data) => request('PUT', `/users/${username}`, data, true),
  saveMatch: (data) => request('POST', '/matches', data, true),
  unlockAchievement: (username, achievementId) =>
    request('POST', `/users/${username}/achievements/${achievementId}`, null, true),

  // Achievements
  getAchievements: () => request('GET', '/achievements', null, true),

  // Friends
  getFriends: (username) => request('GET', `/users/${username}/friends`, null, true),
  addFriend: (me, them) => request('POST', `/users/${me}/friends/${them}`, null, true),
  removeFriend: (me, them) => request('DELETE', `/users/${me}/friends/${them}`, null, true),
};
