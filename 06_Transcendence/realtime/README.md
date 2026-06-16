# Realtime

The **Realtime** service manages WebSocket connections for real-time game updates and player communication using rooms-based pub/sub architecture.

## Overview

The Realtime service provides:
- **WebSocket Server**: Handles persistent client connections
- **Room-based Broadcasting**: Groups players by game room
- **Message Protocol**: Standardized JSON message format
- **Redis Integration**: Subscribes to game state updates from the Engine
- **Chat Support**: In-game messaging between players
- **Health Monitoring**: Heartbeat mechanism with slow client detection

## Architecture

realtime/
├── src/
│   ├── index.ts # Main server entry point
│   ├── wsServer.ts # WebSocket server setup and handlers
│   ├── rooms.ts # Room registry and broadcast logic
│   ├── protocol.ts # Message type definitions and parsing
│   ├── chat.ts # Chat message handling
│   ├── redisSubscriber.ts # Redis pub/sub listener
│   └── package.json
├── tsconfig.json # TypeScript configuration
└── README.md

## Key Components

### WebSocket Server (`wsServer.ts`)

Manages client connections with:
- **Heartbeat Monitoring**: Ping/pong every 25 seconds
- **Slow Client Detection**: Terminates connections with >1MB buffered data
- **Message Parsing**: Validates and parses incoming messages
- **Error Handling**: Graceful handling of connection errors

### Room Registry (`rooms.ts`)

Handles room-based message broadcasting:
- **join(roomId, playerId, ws)**: Add player to room
- **leave(ws)**: Remove player from room
- **broadcast(roomId, msg, exclude?)**: Send message to all players in room
- **Automatic Cleanup**: Removes empty rooms

Features:
- Weakly-referenced metadata (auto-cleanup on WebSocket close)
- Player join/leave notifications
- Player count updates

### Message Protocol (`protocol.ts`)

#### Client -> Server Messages

```TypeScript
// Join a game room
{ type: 'join', roomId: string, playerId: string }

// Leave current room
{ type: 'leave' }

// Send chat message
{ type: 'chat', text: string }

// Heartbeat
{ type: 'ping' }
```

#### Server -> Client Messages

```TypeScript
// Confirmation of join
{ type: 'joined', roomId: string }

// Game state update
{ type: 'state', state: unknown }

// Chat message
{ type: 'chat', from: string, text: string, ts: number }

// Error response
{ type: 'error', code: string, message: string }

// Heartbeat response
{ type: 'pong' }
```

### Redis Subscriber (redisSubscriber.ts)

Listens for Engine-published events:
- Game state updates
- Match results
- Player actions
Publishes updates to all connected clients in affected rooms.

### Chat Handler (chat.ts)
Processes chat messages:

- Message validation (length limits)
- Broadcasting to room
- Timestamp tracking

## Running the Service

```bash
# Install dependencies
npm install

# Development with hot reload
npm run dev

# Production build
npm run build
npm start
```

## Connection Flow

Client connects
    |
    v
Send 'join' message with roomId and playerId
    |
    v
Server adds to RoomRegistry
    |
    v
Receive 'joined' confirmation
    |
    v
Send/receive messages in room
    |
    v
Heartbeat ping/pong every 25s
    |
    v
Send 'leave' or disconnect
    |
    v
Server removes from room

## Performance Characteristics

- **Connections per Server**: Scales to 10,000+ concurrent WebSocket connections
- **Message Latency**: <50ms typical (in-memory broadcast)
- **Memory per Connection**: ~2-5KB baseline
- **Redis Throughput**: Handles Engine state updates at game tick rate

## Backpressure & Flow Control

The server implements soft backpressure:

- Monitors ws.bufferedAmount (unsent data in buffer)
- Terminates slow clients if buffer exceeds 1MB
- Prevents server memory exhaustion under load

## Scaling Considerations

For multi-server deployments:

1. **Sticky Sessions**: Client must connect to same server instance
2. **Redis Coordination**: All servers subscribe to shared Redis channels
3. **Load Balancer**: Configure for WebSocket affinity
4. **Horizontal Scaling**: Start multiple instances on different ports

Example with multiple servers:

Server A (port 42069) ─┐
Server B (port 42070) ─┼─> Redis <- Engine updates
Server C (port 42071) ─┘

## Troubleshooting

### Clients Can't Connect

```bash
# Check if server is running
lsof -i :42069

# Verify Redis connectivity
redis-cli ping
```

### Message Loss

- Check Redis connection: REDIS_URL must be correct
- Verify Engine is publishing: look for PUBLISH calls
- Check client heartbeat: ping/pong every 25s is expected

### High Memory Usage

- Check for accumulating connections: should equal active players
- Verify slow clients are being terminated
- Monitor Redis pub/sub subscriptions

## Related Documentation

/client/README.md - Great Risk client and game mechanics
/database/README.md - Database and REST API
/engine/README.md - Engine Service - Game state publisher
/enginx/README.md - Nginx - WebSocket reverse proxy and load balancer
/README.md - Global project readme