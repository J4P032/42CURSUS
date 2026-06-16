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

export default function Chat({ messages, onSend, status, playerId, onOpenProfile }) {
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

    window.addEventListener('pointermove', onMove);
    window.addEventListener('pointerup', onUp);
    window.addEventListener('pointercancel', onUp);
    return () => {
      window.removeEventListener('pointermove', onMove);
      window.removeEventListener('pointerup', onUp);
      window.removeEventListener('pointercancel', onUp);
    };
  }, [dragging]);

  useEffect(() => {
    function onResize() {
      setPos((prev) => (prev ? clampToViewport(prev.x, prev.y, boxRef.current) : prev));
    }
    window.addEventListener('resize', onResize);
    return () => window.removeEventListener('resize', onResize);
  }, []);

  function onPointerDown(e) {
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

  const positionStyle = {
    top: pos?.y ?? 0,
    left: pos?.x ?? 0,
    visibility: pos ? 'visible' : 'hidden',
    cursor: dragging ? 'grabbing' : 'grab',
  };

  const containerClass =
    'fixed z-20 flex w-[260px] touch-none select-none flex-col rounded-md border-2 border-[#6496FF] bg-[#0f0f0f] p-2 font-mono text-[#E0E0E0] shadow-[0_0_20px_rgba(0,0,0,0.5)] sm:w-[280px]';

  if (minimized) {
    return (
      <div ref={boxRef} onPointerDown={onPointerDown} className={`${containerClass} min-h-0`} style={positionStyle}>
        <div
          onClick={() => setMinimized(false)}
          className="flex cursor-pointer items-center justify-between text-[11px] font-bold text-[#6496FF]"
        >
          <span>CHAT {messages.length > 0 && `(${messages.length})`} {playerCount && `• ${playerCount} online`}</span>
          <span>▲</span>
        </div>
      </div>
    );
  }

  return (
    <div
      ref={boxRef}
      onPointerDown={onPointerDown}
      className={`${containerClass} max-h-[220px] min-h-[160px]`}
      style={positionStyle}
    >
      <div
        onClick={() => setMinimized(true)}
        className="mb-1 flex cursor-pointer items-center justify-between text-xs font-bold text-[#6496FF]"
      >
        <span>Chat {disabled && `(${status})`} {playerCount && `• ${playerCount} online`}</span>
        <span className="text-[10px]">▼</span>
      </div>
      <div
        ref={listRef}
        className="mb-1.5 flex-1 select-text overflow-y-auto rounded bg-black/40 p-1.5 text-left text-xs"
        onPointerDown={(e) => e.stopPropagation()}
      >
        {messages.length === 0 && <div className="italic text-[#666]">No messages yet</div>}
        {messages.map((m, i) => {
          const isServer = m.from === 'Server';
          const color = m.from === playerId ? '#FFD700' : (isServer ? '#4CAF50' : '#6496FF');
          const clickable = !isServer && onOpenProfile;
          return (
            <div key={i} className="mb-0.5">
              {clickable ? (
                <button
                  onClick={() => onOpenProfile(m.from)}
                  className="cursor-pointer border-0 bg-transparent p-0 font-mono text-xs hover:underline"
                  style={{ color }}
                >
                  {m.from}
                </button>
              ) : (
                <span style={{ color, fontWeight: isServer ? 'bold' : 'normal' }}>
                  {isServer ? `[${m.from}]` : m.from}
                </span>
              )}
              <span className="text-[#888]">: </span>
              <span style={{ fontStyle: isServer ? 'italic' : 'normal' }}>{m.text}</span>
            </div>
          );
        })}
      </div>
      <form onSubmit={submit} className="flex gap-1" onPointerDown={(e) => e.stopPropagation()}>
        <input
          type="text"
          value={draft}
          onChange={(e) => setDraft(e.target.value)}
          maxLength={1000}
          disabled={disabled}
          placeholder={disabled ? 'Connecting…' : 'Type a message'}
          className="flex-1 rounded-[3px] border border-[#333] bg-[#1a1a1a] px-1.5 py-1 font-mono text-xs text-[#E0E0E0] outline-none"
        />
        <button
          type="submit"
          disabled={disabled || !draft.trim()}
          className="rounded-[3px] border-0 bg-[#6496FF] px-2.5 py-1 text-xs font-bold text-white disabled:cursor-not-allowed disabled:opacity-50 enabled:cursor-pointer"
        >
          Send
        </button>
      </form>
    </div>
  );
}
