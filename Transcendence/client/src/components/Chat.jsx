import { useEffect, useRef, useState } from 'react';

const POS_STORAGE_KEY = 'chat:pos';
const EDGE_MARGIN = 20;

function loadPosFromSession() {
  try {
    const raw = sessionStorage.getItem(POS_STORAGE_KEY);
    if (!raw) return null;
    const parsed = JSON.parse(raw);
    if (typeof parsed?.x === 'number' && typeof parsed?.y === 'number') {
      return parsed;
    }
  } catch {
    // ignore
  }
  return null;
}

function clampToViewport(x, y, el) {
  if (!el) return { x, y };
  const maxX = Math.max(0, window.innerWidth - el.offsetWidth);
  const maxY = Math.max(0, window.innerHeight - el.offsetHeight);
  return {
    x: Math.max(0, Math.min(maxX, x)),
    y: Math.max(0, Math.min(maxY, y)),
  };
}

export default function Chat({ messages, onSend, status, playerId }) {
  const [draft, setDraft] = useState('');
  const [minimized, setMinimized] = useState(false);
  const [pos, setPos] = useState(() => loadPosFromSession());
  const [dragging, setDragging] = useState(false);
  const dragOffsetRef = useRef({ dx: 0, dy: 0 });
  const boxRef = useRef(null);
  const listRef = useRef(null);

  useEffect(() => {
    const el = listRef.current;
    if (el && !minimized) el.scrollTop = el.scrollHeight;
  }, [messages, minimized]);

  useEffect(() => {
    if (pos !== null || !boxRef.current) return;
    const el = boxRef.current;
    const x = window.innerWidth - el.offsetWidth - EDGE_MARGIN;
    const y = window.innerHeight - el.offsetHeight - EDGE_MARGIN;
    setPos(clampToViewport(x, y, el));
  }, [pos, minimized]);

  useEffect(() => {
    if (pos) sessionStorage.setItem(POS_STORAGE_KEY, JSON.stringify(pos));
  }, [pos]);

  useEffect(() => {
    if (!dragging) return;
    function onMove(e) {
      const { dx, dy } = dragOffsetRef.current;
      setPos(clampToViewport(e.clientX - dx, e.clientY - dy, boxRef.current));
    }
    function onUp() { setDragging(false); }
    window.addEventListener('mousemove', onMove);
    window.addEventListener('mouseup', onUp);
    return () => {
      window.removeEventListener('mousemove', onMove);
      window.removeEventListener('mouseup', onUp);
    };
  }, [dragging]);

  useEffect(() => {
    function onResize() {
      setPos((prev) => (prev ? clampToViewport(prev.x, prev.y, boxRef.current) : prev));
    }
    window.addEventListener('resize', onResize);
    return () => window.removeEventListener('resize', onResize);
  }, []);

  function onMouseDown(e) {
    if (e.target.closest('form') || e.target.closest('button')) return;
    if (!pos) return;
    e.preventDefault();
    dragOffsetRef.current = { dx: e.clientX - pos.x, dy: e.clientY - pos.y };
    setDragging(true);
  }

  function submit(e) {
    e.preventDefault();
    if (!draft.trim()) return;
    if (onSend(draft)) setDraft('');
  }

  const disabled = status !== 'open';
  const serverMessages = messages.filter(m => m.from === 'Server' && m.text.includes('Players connected'));
  const playerCountMatch = serverMessages[serverMessages.length - 1]?.text.match(/\d+/);
  const playerCount = playerCountMatch ? playerCountMatch[0] : null;

  const containerStyle = {
    position: 'fixed',
    top: pos?.y ?? 0,
    left: pos?.x ?? 0,
    width: '280px',
    zIndex: 20,
    visibility: pos ? 'visible' : 'hidden',
    cursor: dragging ? 'grabbing' : 'grab',
    userSelect: 'none',
    display: 'flex',
    flexDirection: 'column',
    backgroundColor: '#0f0f0f',
    border: '2px solid #6496FF',
    borderRadius: '6px',
    padding: '8px',
    fontFamily: 'monospace',
    color: '#E0E0E0',
    boxShadow: '0 0 20px rgba(0,0,0,0.5)',
  };

  if (minimized) {
    return (
      <div ref={boxRef} onMouseDown={onMouseDown} style={{ ...containerStyle, minHeight: 'auto' }}>
        <div onClick={() => setMinimized(false)} style={{ cursor: 'pointer', fontWeight: 'bold', display: 'flex', justifyContent: 'space-between', alignItems: 'center', fontSize: '11px', color: '#6496FF' }}>
          <span>CHAT {messages.length > 0 && `(${messages.length})`} {playerCount && `• ${playerCount} online`}</span>
          <span>▲</span>
        </div>
      </div>
    );
  }

  return (
    <div ref={boxRef} onMouseDown={onMouseDown} style={{ ...containerStyle, minHeight: '160px', maxHeight: '220px' }}>
      <div onClick={() => setMinimized(true)} style={{ display: 'flex', justifyContent: 'space-between', alignItems: 'center', color: '#6496FF', fontWeight: 'bold', marginBottom: '4px', cursor: 'pointer', fontSize: '12px' }}>
        <span>Chat {disabled && `(${status})`} {playerCount && `• ${playerCount} online`}</span>
        <span style={{ fontSize: '10px' }}>▼</span>
      </div>
      <div ref={listRef} style={{ flex: 1, overflowY: 'auto', backgroundColor: 'rgba(0,0,0,0.4)', padding: '6px', borderRadius: '4px', marginBottom: '6px', textAlign: 'left', userSelect: 'text', fontSize: '12px' }} onMouseDown={(e) => e.stopPropagation()}>
        {messages.length === 0 && <div style={{ color: '#666', fontStyle: 'italic' }}>No messages yet</div>}
        {messages.map((m, i) => (
          <div key={i} style={{ marginBottom: '2px' }}>
            <span style={{ color: m.from === playerId ? '#FFD700' : (m.from === 'Server' ? '#4CAF50' : '#6496FF'), fontWeight: m.from === 'Server' ? 'bold' : 'normal' }}>
              {m.from === 'Server' ? `[${m.from}]` : m.from}
            </span>
            <span style={{ color: '#888' }}>: </span>
            <span style={{ fontStyle: m.from === 'Server' ? 'italic' : 'normal' }}>{m.text}</span>
          </div>
        ))}
      </div>
      <form onSubmit={submit} style={{ display: 'flex', gap: '4px' }} onMouseDown={(e) => e.stopPropagation()}>
        <input type="text" value={draft} onChange={(e) => setDraft(e.target.value)} maxLength={1000} disabled={disabled} placeholder={disabled ? 'Connecting…' : 'Type a message'} style={{ flex: 1, padding: '4px 6px', fontSize: '12px', fontFamily: 'monospace', backgroundColor: '#1a1a1a', color: '#E0E0E0', border: '1px solid #333', borderRadius: '3px', outline: 'none' }} />
        <button type="submit" disabled={disabled || !draft.trim()} style={{ padding: '4px 10px', fontSize: '12px', backgroundColor: '#6496FF', color: 'white', border: 'none', borderRadius: '3px', cursor: disabled ? 'not-allowed' : 'pointer', fontWeight: 'bold', opacity: disabled || !draft.trim() ? 0.5 : 1 }}>Send</button>
      </form>
    </div>
  );
}
