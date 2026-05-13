import { useEffect, useRef, useState } from 'react';

export default function Chat({ messages, onSend, status, playerId }) {
  const [draft, setDraft] = useState('');
  const listRef = useRef(null);

  useEffect(() => {
    const el = listRef.current;
    if (el) el.scrollTop = el.scrollHeight;
  }, [messages]);

  function submit(e) {
    e.preventDefault();
    if (!draft.trim()) return;
    if (onSend(draft)) setDraft('');
  }

  const disabled = status !== 'open';

  return (
    <div
      style={{
        display: 'flex',
        flexDirection: 'column',
        backgroundColor: '#0f0f0f',
        border: '2px solid #6496FF',
        borderRadius: '6px',
        padding: '8px',
        fontFamily: 'monospace',
        fontSize: '12px',
        color: '#E0E0E0',
        minHeight: '160px',
        maxHeight: '220px',
      }}
    >
      <div style={{ color: '#6496FF', fontWeight: 'bold', marginBottom: '4px' }}>
        Chat {disabled && <span style={{ color: '#FF6B6B' }}>({status})</span>}
      </div>
      <div
        ref={listRef}
        style={{
          flex: 1,
          overflowY: 'auto',
          backgroundColor: 'rgba(0,0,0,0.4)',
          padding: '6px',
          borderRadius: '4px',
          marginBottom: '6px',
        }}
      >
        {messages.length === 0 && (
          <div style={{ color: '#666', fontStyle: 'italic' }}>No messages yet</div>
        )}
        {messages.map((m, i) => (
          <div key={i} style={{ marginBottom: '2px' }}>
            <span style={{ color: m.from === playerId ? '#FFD700' : '#6496FF' }}>{m.from}</span>
            <span style={{ color: '#888' }}>: </span>
            <span>{m.text}</span>
          </div>
        ))}
      </div>
      <form onSubmit={submit} style={{ display: 'flex', gap: '4px' }}>
        <input
          type="text"
          value={draft}
          onChange={(e) => setDraft(e.target.value)}
          maxLength={1000}
          disabled={disabled}
          placeholder={disabled ? 'Connecting…' : 'Type a message'}
          style={{
            flex: 1,
            padding: '4px 6px',
            fontSize: '12px',
            fontFamily: 'monospace',
            backgroundColor: '#1a1a1a',
            color: '#E0E0E0',
            border: '1px solid #333',
            borderRadius: '3px',
            outline: 'none',
          }}
        />
        <button
          type="submit"
          disabled={disabled || !draft.trim()}
          style={{
            padding: '4px 10px',
            fontSize: '12px',
            backgroundColor: '#6496FF',
            color: 'white',
            border: 'none',
            borderRadius: '3px',
            cursor: disabled ? 'not-allowed' : 'pointer',
            fontWeight: 'bold',
            opacity: disabled || !draft.trim() ? 0.5 : 1,
          }}
        >
          Send
        </button>
      </form>
    </div>
  );
}
