# Engine

The **Engine** service is the core game state and logic handler for the transcendence multiplayer strategy game. It manages game rooms, player turns, territory control, and match persistence.

## Overview

The Engine is an Express.js REST API service that handles:
- **Game State Management**: Manages active game instances and player state
- **Turn Processing**: Processes reinforcement and attack actions
- **Room Orchestration**: Creates and manages game rooms
- **Match Persistence**: Saves match results to the database
- **Real-time Publishing**: Publishes game state changes to the realtime service via Redis

## Architecture

```
engine/
└── src/
    ├── index.js # Main Express app entry point
    ├── gameState.js # Core game state logic
    ├── routes/
    │   ├── rooms.js # Room management endpoints
    │   ├── games.js # Game action endpoints (start, attack, reinforce)
    │   └── players.js # Player endpoints (stats, achievements)
    ├── dbhandler/
    │   └── client.js # Database abstraction layer
    └── messaging/
    └── redisPublisher.js # Redis pub/sub for state broadcasting
```

## Key Components

### Routes

#### `/rooms` - Room Management
- `GET /rooms` - List all active rooms
- `POST /rooms` - Create a new room
- `GET /rooms/:roomId` - Get room details
- `DELETE /rooms/:roomId` - Delete/end a room

#### `/rooms/:roomId/game` - Game Actions
- `POST /rooms/:roomId/game/start` - Start a new game with specified factions
- `GET /rooms/:roomId/game/state` - Retrieve current game state
- `POST /rooms/:roomId/game/reinforce` - Reinforce a territory
- `POST /rooms/:roomId/game/attack` - Execute an attack action

#### `/players` - Player Management
- `GET /rooms/:roomId/players/:id` - Get player stats
- `POST /matches` - Record a match result
- `POST /players/:id/achievements` - Unlock an achievement

### Game State

The `Gamestate` class handles:
- Turn-based game logic
- Territory ownership tracking
- Army/troop management
- Win condition evaluation
- Stats accumulation (territories conquered, turns played)

### Database Handler

Two implementations available:

- **InMemoryDBHandler**: Ephemeral storage (development/testing)
- **HttpDBHandler**: Persists to database service (production)

Switch implementations via the `DBHANDLER_URL` environment variable.

## Environment Variables

```env
PORT=3000                              # Express server port
REDIS_URL=redis://localhost:6379       # Redis connection for pub/sub
DBHANDLER_URL=http://db-service:4000   # Database service URL (optional)
```

## Running the Service

```bash
# Install dependencies
npm install

# Start in development
npm run dev

# Start in production
npm start
```

## Integration with Other Services

- **Realtime**: Game state changes are published to Redis, which the realtime service subscribes to
- **Database**: Match results and player achievements are persisted asynchronously
- **Frontend**: Game state is served via REST endpoints and pushed via WebSocket (via realtime)

## Related Documentation

/client/README.md - Great Risk client and game mechanics
/database/README.md - Database and REST API
/realtime/README.md - Realtime Service - WebSocket connection handler
/enginx/README.md - Nginx - WebSocket reverse proxy and load balancer
/README.md - Global project readme