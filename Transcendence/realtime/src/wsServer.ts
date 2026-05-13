import { WebSocketServer, WebSocket } from 'ws';
import { parseClientMsg } from './protocol.js';
import { handleChat } from './chat.js';
import type { RoomRegistry } from './rooms.js';

const HEARTBEAT_MS = 25_000;

interface AliveSocket extends WebSocket {
  isAlive: boolean;
}

function send(ws: WebSocket, payload: object): void {
  if (ws.readyState === ws.OPEN) ws.send(JSON.stringify(payload));
}

export function startWsServer(port: number, rooms: RoomRegistry): WebSocketServer {
  const wss = new WebSocketServer({ port, host: '0.0.0.0' });

  const heartbeat = setInterval(() => {
    for (const client of wss.clients) {
      const c = client as AliveSocket;
      if (!c.isAlive) {
        rooms.leave(c);
        c.terminate();
        continue;
      }
      c.isAlive = false;
      try {
        c.ping();
      } catch {
        // ignore — terminate next tick
      }
    }
  }, HEARTBEAT_MS);

  wss.on('close', () => clearInterval(heartbeat));

  wss.on('connection', (ws) => {
    const sock = ws as AliveSocket;
    sock.isAlive = true;

    sock.on('pong', () => {
      sock.isAlive = true;
    });

    sock.on('message', (data) => {
      const raw = data.toString();
      const msg = parseClientMsg(raw);
      if (!msg) {
        send(sock, { type: 'error', code: 'bad_message', message: 'Malformed message' });
        return;
      }

      switch (msg.type) {
        case 'join':
          rooms.join(msg.roomId, msg.playerId, sock);
          send(sock, { type: 'joined', roomId: msg.roomId });
          break;
        case 'leave':
          rooms.leave(sock);
          break;
        case 'chat':
          handleChat(sock, msg.text, rooms);
          break;
        case 'ping':
          send(sock, { type: 'pong' });
          break;
      }
    });

    sock.on('close', () => {
      rooms.leave(sock);
    });

    sock.on('error', (err) => {
      console.error('[ws] socket error:', err.message);
      rooms.leave(sock);
    });
  });

  wss.on('listening', () => {
    console.log(`[ws] listening on :${port}`);
  });

  return wss;
}
