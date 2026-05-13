import { useEffect, useRef, useState, useCallback } from 'react';
import { wsUrl } from '../api.js';

const MIN_BACKOFF_MS = 200;
const MAX_BACKOFF_MS = 10_000;
const PING_INTERVAL_MS = 25_000;

export default function useGameSocket({ roomId, playerId, onState, onChat }) {
  const [status, setStatus] = useState('idle');
  const wsRef = useRef(null);
  const onStateRef = useRef(onState);
  const onChatRef = useRef(onChat);
  const closedByUserRef = useRef(false);
  const reconnectAttemptsRef = useRef(0);
  const reconnectTimerRef = useRef(null);
  const pingTimerRef = useRef(null);

  useEffect(() => {
    onStateRef.current = onState;
  }, [onState]);
  useEffect(() => {
    onChatRef.current = onChat;
  }, [onChat]);

  useEffect(() => {
    if (!roomId || !playerId) return undefined;
    closedByUserRef.current = false;

    function clearTimers() {
      if (reconnectTimerRef.current) {
        clearTimeout(reconnectTimerRef.current);
        reconnectTimerRef.current = null;
      }
      if (pingTimerRef.current) {
        clearInterval(pingTimerRef.current);
        pingTimerRef.current = null;
      }
    }

    function scheduleReconnect() {
      if (closedByUserRef.current) return;
      const attempt = reconnectAttemptsRef.current++;
      const delay = Math.min(MIN_BACKOFF_MS * 2 ** attempt, MAX_BACKOFF_MS);
      setStatus('reconnecting');
      reconnectTimerRef.current = setTimeout(connect, delay);
    }

    function connect() {
      setStatus('connecting');
      let ws;
      try {
        ws = new WebSocket(wsUrl());
      } catch {
        scheduleReconnect();
        return;
      }
      wsRef.current = ws;

      ws.addEventListener('open', () => {
        reconnectAttemptsRef.current = 0;
        setStatus('open');
        ws.send(JSON.stringify({ type: 'join', roomId, playerId }));
        pingTimerRef.current = setInterval(() => {
          if (ws.readyState === WebSocket.OPEN) {
            ws.send(JSON.stringify({ type: 'ping' }));
          }
        }, PING_INTERVAL_MS);
      });

      ws.addEventListener('message', (event) => {
        let msg;
        try {
          msg = JSON.parse(event.data);
        } catch {
          return;
        }
        if (msg.type === 'state' && onStateRef.current) onStateRef.current(msg.state);
        else if (msg.type === 'chat' && onChatRef.current) onChatRef.current(msg);
      });

      ws.addEventListener('close', () => {
        clearTimers();
        wsRef.current = null;
        if (closedByUserRef.current) {
          setStatus('closed');
          return;
        }
        scheduleReconnect();
      });

      ws.addEventListener('error', () => {
        // close handler will fire next; nothing to do here
      });
    }

    connect();

    return () => {
      closedByUserRef.current = true;
      clearTimers();
      const ws = wsRef.current;
      wsRef.current = null;
      if (ws && ws.readyState === WebSocket.OPEN) {
        try {
          ws.send(JSON.stringify({ type: 'leave' }));
        } catch {
          // ignore
        }
      }
      if (ws) ws.close();
    };
  }, [roomId, playerId]);

  const sendChat = useCallback((text) => {
    const ws = wsRef.current;
    if (!ws || ws.readyState !== WebSocket.OPEN) return false;
    const trimmed = String(text ?? '').trim();
    if (!trimmed) return false;
    ws.send(JSON.stringify({ type: 'chat', text: trimmed }));
    return true;
  }, []);

  return { status, sendChat };
}
