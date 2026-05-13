# Great Risk - Strategy Game

A turn-based strategy game inspired by Risk, built with React and Vite. Players control different factions competing for territorial dominance across a historical European map.

## Features

### Core Gameplay

- **Turn-based strategy system** with multiple game phases (Reinforce, Attack, Fortify)
- **45 Interactive territories** across Europe with bilateral neighbor connections
- **Dynamic Canvas Scaling** - Territories normalized to 0-1 coordinates for responsive rendering
- **Troop count display** - Numbers shown directly inside territory circles
- **6 Playable factions** with unique names and colors:
  - 🔵 **Francia** (Blue) - #0055FF
  - 🟡 **España** (Gold) - #FFD700
  - 🔴 **Inglaterra** (Red) - #FF0000
  - ⚪ **Austria** (Off-white) - #E8E8E8
  - 🟢 **Rusia** (Green) - #00AA00
  - 🔻 **Otomanos** (Dark Red) - #8B0000

### Game Mechanics

- Territory ownership and troop management (2-3 troops per territory based on regional capital status)
- **Three game phases**:
  - **Reinforce (Refuerzos)**: Deploy reinforcements based on territory count (minimum 3, plus 1 per 3 territories)
  - **Attack (Ataque)**: Conquer adjacent territories with dice-based combat (1-3 troops max per attack)
  - **Fortify (Fortificación)**: Move troops between neighboring territories (unlimited troops can move)
- One-attack-per-territory restriction (defenders can defend unlimited times)
- Combat resolution with automatic dice rolling
- Territory conquest with automatic troop movement
- Canvas-based rendering with color-picking for territory selection
- Turn rotation between players with turn counter
- **Battle Report Overlay** with detailed combat information (troops, dice rolls, casualties, conquest status)
- **Province Hover Highlighting** with territory info box (name, owner, troop count)
- **Unified Dark Theme UI** with red/blue battle aesthetic throughout
- **Filled Province Shapes** - Entire territory regions rendered in faction colors, not just center circles
- **Territory Circles with Troop Display** - White numbers centered inside colored circles, rendering above connection lines
- **Optimized Canvas Rendering** - Offscreen territory canvas cache for high-performance province rendering

### Rendering System

- **Dual-Canvas Architecture**:
  - **Picking Canvas**: Hidden canvas with color-coded territories for click detection
  - **Territory Canvas**: Offscreen cache storing pre-rendered filled provinces
  - **Main Canvas**: Visible interactive game board
- **Pixel-Based Province Fills**: Uses cached pixel data from map to fill provinces with faction colors
- **Performance Optimization**: Territory canvas only redraws when ownership changes, not every frame
- **Visual Hierarchy**: Background map → Territory fills → Connection lines → Territory points → Effects

### Victory Conditions

Two distinct ways to win:

1. **Capital Conquest** 🏰

   - Capture all enemy faction capitals
   - Each faction has a unique capital territory:
     - France: France
     - Spain: Spain
     - England: England
     - Austria: Austria
     - Russia: Moscow
     - Ottomans: Constantinople
   - Immediate victory upon conquering all enemy capitals

2. **Score Victory** 🏆
   - After 100 turns, highest score wins
   - **Scoring system**:
     - Normal territory: 1 point
     - Regional capital: 2 points
     - Enemy faction capital: 3 points
   - Automatic calculation when turn limit reached

### Regional Capitals

Some territories are designated as regional capitals with strategic importance:

- Start with **3 troops** instead of 2
- Worth **2 points** in score-based victory
- Examples: England, France, Sweden, Brandenburg, East Prussia, Spain, Austria, etc.
- Each faction has a unique **faction capital** that triggers instant victory if conquered by enemies

## Project Structure

The repository is an npm-workspaces monorepo. Game-rule modules live in the
top-level `shared/` package (`@trascendence/shared`) and are consumed by both
this client and the `engine/` REST API service.

```
trascendence/
├── shared/                     # @trascendence/shared — pure rule modules
│   ├── Territories.js          # Territory data with neighbors & capitals
│   ├── Factions.js             # Faction definitions with capitals
│   ├── Player.js               # Player class and factory
│   ├── TurnManager.js          # Turn, phase, & combat management
│   ├── Victory.js              # Victory condition checkers
│   └── validateConnections.js  # Territory connection validator
├── engine/                     # Core Game REST API (Express, Node)
├── realtime/                   # WebSocket fan-out (TS, ws, Redis sub)
└── client/                     # this package — React client
    ├── src/
    │   ├── components/
    │   │   └── Gameboard.jsx
    │   └── assets/
    │       └── map_picking.png
    └── …
```

## Development

### Local Setup (Without Docker)

Install once at the **repo root** (npm workspaces):

```bash
# from the repo root
npm install
```

Then in two terminals:

```bash
# Terminal 1 — REST API
node engine/src/index.js

# Terminal 2 — React dev server (HMR on http://localhost:5173)
npm run dev -w client
```

The client communicates with the API at `http://localhost:3000` by default
(configurable via `VITE_API_URL`). For real-time updates you also need
`realtime/` and a local Redis running — easier via Docker (below).

### Docker Setup (Recommended)

The project is containerized with Docker Compose, orchestrated from the **repository root** (one level above `client/`):

- **Redis** (Pub/Sub broker): internal-only, not exposed
- **Realtime** (TypeScript WebSocket service): port `42069`
- **Engine** (Core Game REST API, Node.js): port `3000`
- **Client** (React frontend, Nginx): port `80`

```bash
# from the repo root, NOT from client/
docker-compose up --build
```

Access the game at `http://localhost` (Nginx on port 80).

**Real-time architecture**:

- The REST API publishes `game:<roomId>:state` to Redis after every state mutation.
- The `realtime` service subscribes via `psubscribe game:*:state` and fans messages out to all WebSocket clients in the matching room.
- The client opens a single WebSocket to `ws://<host>:42069`, sends `{ type: 'join', roomId, playerId }`, and receives `state` and `chat` pushes.
- Chat is ephemeral (no persistence, no history).

**Docker Configuration**:

- Client: Multi-stage build with Node.js builder (root context, resolves the `shared` workspace) and Nginx production server
- Engine: Node.js service built from the repo root so the `shared` workspace resolves
- Realtime: Multi-stage TypeScript build, runs `node dist/index.js`
- Services restart automatically unless manually stopped

### Validation

Verify that all territory connections are bilateral:

```bash
npm run validate:territories -w client
# or directly:
node shared/validateConnections.js
```

This ensures map integrity, especially useful when expanding the map with new territories.

### Build

```bash
npm run build
```

### Linting

```bash
npm run lint
```

## Game Flow

1. **Initialization**: Game state is fetched from the backend API
2. **Turn Structure**:
   - Player enters **REINFORCE** phase with reinforcements based on owned territories (minimum 3 troops, +1 per 3 territories owned)
   - Player enters **ATTACK** phase to conquer enemy territories (1-3 troops per attack, one attack per territory)
   - Player enters **FORTIFY** phase to move troops between neighboring territories
3. **Combat**:
   - Attacker selects territory and enemy target (must be adjacent)
   - Chooses number of attacking troops (1-3)
   - Automatic dice rolling determines casualties
   - Defending territory changes faction if all troops lost
4. **Victory Check**: After each phase:
   - Check if faction owns all enemy capitals (instant win)
   - Check if turn limit (100) exceeded → score-based winner
5. **Game End**: Winner displayed with victory screen and restart option

## Technical Stack

- **React 19.2.4** - UI framework
- **Vite 8.0.0** - Build tool with HMR
- **Canvas API** - Territory rendering and interaction
- **ES6+ Modules** - Clean code organization
- **Docker & Docker Compose** - Containerization and orchestration (compose file lives at repo root)
- **Nginx** - Production web server
- **Node.js 20 (Alpine)** - Backend runtime
- **TypeScript + `ws` + `ioredis`** - Realtime microservice (`realtime/`)
- **Redis 7 (Alpine)** - Pub/Sub broker for state fan-out

## UI Design & Aesthetic

### Color Scheme (Dark Battle Theme)

- **Background**: `#0d0d0d` (deep dark gray)
- **Primary Red** (Battle/Combat): `#FF6B6B` (with hover: `#FF5252`)
- **Primary Blue** (Attackers): `#6496FF`
- **Accent Gold** (Highlights): `#FFD700`
- **Success Green** (Fortify): `#4CAF50` (with hover: `#45a049`)
- **Text**: `#E0E0E0` (light gray)

### UI Components

- **Title**: Red (#FF6B6B) with sword emojis (⚔️) and text shadow glow
- **Canvas**: 3px red border with 20px glow shadow effect
- **Territory Info Box**: Blue border with dark background, city/troop details
- **Bottom Panel**: Three-way layout
  - **LEFT**: Player data (blue name, gold faction, red phase indicator)
  - **CENTER**: Turn counter and red "Next Turn" button with hover glow
  - **RIGHT**: Action controls (green Fortify, red Attack buttons)
- **Battle Report**: Red border with detailed combat grid (blue attacker, red defender)
- **Winner Modal**: Red border with victory message and green restart button
- **All Buttons**: Smooth transitions with hover glow effects
