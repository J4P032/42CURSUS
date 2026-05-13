import { useState, useEffect } from 'react';
import { FACTIONS } from '@trascendence/shared/Factions';
import { api } from '../api.js';

export default function Lobby({ onStart }) {
  const [screen, setScreen] = useState('home'); // home | create | join | faction
  const [roomId, setRoomId] = useState('');
  const [roomInput, setRoomInput] = useState('');
  const [maxPlayers, setMaxPlayers] = useState(2);
  const [faction, setFaction] = useState(null);
  const [roomData, setRoomData] = useState(null); // datos de la sala
  const [error, setError] = useState(null);
  const [isCreator, setIsCreator] = useState(false);
  const [playerId, setPlayerId] = useState('');

  useEffect(() => {
    // eslint-disable-next-line react-hooks/set-state-in-effect
    setPlayerId(`player-${Math.random().toString(36).slice(2, 7)}`);
  }, []);

	// Polling para actualizar jugadores en sala
	useEffect(() => {
		if (screen !== 'faction' || !roomId) return;

		const interval = setInterval(async () => {
			const res = await api.getRoom(roomId);
			if (!res.ok) return;
			setRoomData(res.room);
			if (res.room.started && faction) {
				clearInterval(interval);
				onStart({ roomId, playerId, faction });
			}
		}, 2000);

  return () => clearInterval(interval);
}, [screen, roomId, faction, onStart, playerId]);

  async function handleCreateRoom() {
    if (!roomInput.trim()) return;
    const res = await api.createRoom(roomInput.trim(), maxPlayers);
    if (!res.ok) { setError(res.error); return; }
    setRoomId(roomInput.trim());
    setIsCreator(true);
    setScreen('faction');
    setError(null);
  }

  async function handleJoinRoom() {
    if (!roomInput.trim()) return;
    const res = await api.getRoom(roomInput.trim());
    if (!res.ok) { setError(res.error); return; }
    if (res.room.started) { setError('Game already started'); return; }
    setRoomId(roomInput.trim());
    setRoomData(res.room);
    setIsCreator(false);
    setScreen('faction');
    setError(null);
  }

  async function handleSelectFaction(factionId) {
    const res = await api.joinRoom(roomId, playerId, FACTIONS[factionId].name, factionId);
    if (!res.ok) { setError(res.error); return; }
    setFaction(factionId);
    setRoomData(res.room);
    setError(null);
  }

  async function handleStart() {
    const res = await api.startRoom(roomId);
    if (!res.ok) { setError(res.error); return; }
    onStart({ roomId, playerId, faction });
  }

  const takenFactions = roomData?.players?.map(p => p.faction) ?? [];
  const allPlayersJoined = roomData && roomData.players.length === roomData.maxPlayers;

  return (
    <div style={{
      maxWidth: '600px',
      margin: '60px auto',
      fontFamily: 'monospace',
      color: 'white',
      backgroundColor: '#1a1a2e',
      padding: '40px',
      borderRadius: '12px',
      border: '2px solid #FF6B6B',
      boxShadow: '0 0 30px rgba(255, 107, 107, 0.3)',
    }}>
      <h1 style={{ textAlign: 'center', color: '#FF6B6B', marginBottom: '4px', letterSpacing: '2px' }}>
        GREAT RISK
      </h1>
      <p style={{ textAlign: 'center', color: '#aaa', marginBottom: '32px' }}>
        Napoleonic Wars
      </p>

      {error && (
        <div style={{ backgroundColor: 'rgba(255,107,107,0.2)', border: '1px solid #FF6B6B', padding: '10px', borderRadius: '4px', marginBottom: '16px', fontSize: '12px', color: '#FF6B6B' }}>
          {error}
        </div>
      )}

      {/* HOME */}
      {screen === 'home' && (
        <div style={{ display: 'flex', gap: '12px' }}>
          <button onClick={() => setScreen('create')} style={btnStyle('#FF6B6B')}>
            Create Room
          </button>
          <button onClick={() => setScreen('join')} style={btnStyle('#6496FF')}>
            Join Room
          </button>
        </div>
      )}

      {/* CREATE */}
      {screen === 'create' && (
        <div>
          <label style={{ display: 'block', marginBottom: '8px', color: '#FFD700' }}>Room Name</label>
          <input
            value={roomInput}
            onChange={e => setRoomInput(e.target.value)}
            placeholder="e.g. waterloo-1815"
            style={inputStyle}
          />
          <label style={{ display: 'block', margin: '16px 0 8px', color: '#FFD700' }}>Players</label>
          <div style={{ display: 'flex', gap: '8px', marginBottom: '20px' }}>
            {[2, 3, 4].map(n => (
              <button key={n} onClick={() => setMaxPlayers(n)}
                style={btnStyle(maxPlayers === n ? '#FF6B6B' : '#333')}>
                {n}
              </button>
            ))}
          </div>
          <button onClick={handleCreateRoom} style={btnStyle('#FF6B6B')}>Create</button>
          <button onClick={() => setScreen('home')} style={{ ...btnStyle('#333'), marginTop: '8px' }}>Back</button>
        </div>
      )}

      {/* JOIN */}
      {screen === 'join' && (
        <div>
          <label style={{ display: 'block', marginBottom: '8px', color: '#FFD700' }}>Room Name</label>
          <input
            value={roomInput}
            onChange={e => setRoomInput(e.target.value)}
            placeholder="Enter room name"
            style={inputStyle}
          />
          <button onClick={handleJoinRoom} style={{ ...btnStyle('#6496FF'), marginTop: '16px' }}>Join</button>
          <button onClick={() => setScreen('home')} style={{ ...btnStyle('#333'), marginTop: '8px' }}>Back</button>
        </div>
      )}

      {/* FACTION SELECTION */}
      {screen === 'faction' && (
        <div>
          <div style={{ marginBottom: '16px', color: '#aaa', fontSize: '12px' }}>
            Room: <span style={{ color: '#FFD700' }}>{roomId}</span>
            {' '}— {roomData?.players?.length ?? 0}/{roomData?.maxPlayers ?? maxPlayers} players
          </div>

          {!faction ? (
            <>
              <label style={{ display: 'block', marginBottom: '12px', color: '#FFD700' }}>
                Choose your faction
              </label>
              <div style={{ display: 'flex', gap: '8px', flexWrap: 'wrap' }}>
                {Object.entries(FACTIONS).map(([factionId, f]) => {
                  const taken = takenFactions.includes(factionId);
                  return (
                    <button key={factionId}
                      onClick={() => !taken && handleSelectFaction(factionId)}
                      style={{
                        padding: '8px 14px',
                        backgroundColor: taken ? '#1a1a1a' : '#333',
                        color: taken ? '#444' : 'white',
                        border: '2px solid #555',
                        borderRadius: '4px',
                        cursor: taken ? 'not-allowed' : 'pointer',
                        fontFamily: 'monospace',
                        fontSize: '12px',
                        opacity: taken ? 0.4 : 1,
                      }}
                    >
                      {f.name}
                    </button>
                  );
                })}
              </div>
            </>
          ) : (
            <div style={{ color: '#4CAF50', marginBottom: '16px' }}>
              ✓ Playing as <strong>{FACTIONS[faction].name}</strong>
            </div>
          )}

          {/* Lista de jugadores en sala */}
          {roomData?.players?.length > 0 && (
            <div style={{ marginTop: '20px' }}>
              <div style={{ color: '#aaa', fontSize: '11px', marginBottom: '8px' }}>IN ROOM:</div>
              {roomData.players.map(p => (
                <div key={p.id} style={{ fontSize: '12px', color: '#E0E0E0', marginBottom: '4px' }}>
                  • {p.name} — <span style={{ color: FACTIONS[p.faction]?.color }}>{FACTIONS[p.faction]?.name}</span>
                </div>
              ))}
            </div>
          )}

          {/* Solo el creador puede iniciar */}
          {isCreator && faction && allPlayersJoined && (
            <button onClick={handleStart} style={{ ...btnStyle('#FF6B6B'), marginTop: '20px' }}>
              Start Campaign
            </button>
          )}

          {isCreator && faction && !allPlayersJoined && (
            <div style={{ marginTop: '16px', color: '#aaa', fontSize: '12px' }}>
              Waiting for {(roomData?.maxPlayers ?? maxPlayers) - (roomData?.players?.length ?? 0)} more player(s)...
            </div>
          )}

          {!isCreator && faction && (
            <div style={{ marginTop: '16px', color: '#aaa', fontSize: '12px' }}>
              Waiting for host to start...
            </div>
          )}
        </div>
      )}
    </div>
  );
}

const btnStyle = (bg) => ({
  width: '100%',
  padding: '10px',
  backgroundColor: bg,
  color: 'white',
  border: 'none',
  borderRadius: '4px',
  cursor: 'pointer',
  fontFamily: 'monospace',
  fontWeight: 'bold',
  fontSize: '13px',
});

const inputStyle = {
  width: '100%',
  padding: '10px',
  backgroundColor: '#333',
  color: 'white',
  border: '2px solid #555',
  borderRadius: '4px',
  fontFamily: 'monospace',
  fontSize: '13px',
  boxSizing: 'border-box',
};