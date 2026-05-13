# Endpoints REST & Ejemplos de CURL

Base URL: `http://localhost:4000`

## 📊 Health Check

```bash
curl http://localhost:4000/health
```

---

## 👥 USUARIOS

### GET - Listar todos los usuarios
```bash
curl http://localhost:4000/users
```

### GET - Obtener usuario específico con todas sus relaciones
```bash
curl http://localhost:4000/users/1
```

### POST - Crear nuevo usuario
```bash
curl -X POST http://localhost:4000/users \
  -H "Content-Type: application/json" \
  -d '{
    "username": "nuevo_jugador",
    "email": "jugador@ejemplo.com",
    "passwordHash": "hash_de_contrasena",
    "avatarUrl": "https://api.dicebear.com/7.x/avataaars/svg?seed=nuevo_jugador"
  }'
```

### PUT - Actualizar usuario
```bash
curl -X PUT http://localhost:4000/users/1 \
  -H "Content-Type: application/json" \
  -d '{
    "username": "nombre_actualizado",
    "email": "nuevo@email.com",
    "avatarUrl": "https://nueva-url-avatar.com/avatar.png"
  }'
```

---

## 📈 ESTADÍSTICAS

### GET - Obtener estadísticas de usuario
```bash
curl http://localhost:4000/users/1/stats
```

### PUT - Actualizar estadísticas
```bash
curl -X PUT http://localhost:4000/users/1/stats \
  -H "Content-Type: application/json" \
  -d '{
    "gamesPlayed": 50,
    "wins": 35,
    "losses": 15,
    "elo": 1900
  }'
```

---

## 👫 AMISTADES

### GET - Listar amigos de un usuario
```bash
curl http://localhost:4000/users/1/friends
```

### POST - Agregar amigo
```bash
curl -X POST http://localhost:4000/users/1/friends/2 \
  -H "Content-Type: application/json"
```

### DELETE - Eliminar amigo
```bash
curl -X DELETE http://localhost:4000/users/1/friends/2
```

---

## 🎮 PARTIDAS

### GET - Listar todas las partidas
```bash
# Sin filtros
curl http://localhost:4000/matches

# Con filtro por estado
curl "http://localhost:4000/matches?status=completed"

# Con filtro por tipo de juego
curl "http://localhost:4000/matches?gameMode=Battle%20Royale"

# Con paginación
curl "http://localhost:4000/matches?skip=0&take=5"
```

### GET - Obtener partida específica
```bash
curl http://localhost:4000/matches/1
```

### POST - Crear nueva partida
```bash
curl -X POST http://localhost:4000/matches \
  -H "Content-Type: application/json" \
  -d '{
    "gameMode": "Battle Royale",
    "maxPlayers": 4,
    "status": "waiting"
  }'
```

### PUT - Actualizar partida (cambiar estado, etc)
```bash
curl -X PUT http://localhost:4000/matches/1 \
  -H "Content-Type: application/json" \
  -d '{
    "status": "completed",
    "startedAt": "2026-05-10T10:30:00Z",
    "endedAt": "2026-05-10T10:50:00Z"
  }'
```

### POST - Agregar jugador a partida
```bash
curl -X POST http://localhost:4000/matches/1/players/2 \
  -H "Content-Type: application/json" \
  -d '{
    "score": 0,
    "position": null
  }'
```

### PUT - Actualizar jugador en partida (actualizar puntuación, posición)
```bash
curl -X PUT http://localhost:4000/match-players/1 \
  -H "Content-Type: application/json" \
  -d '{
    "score": 2500,
    "position": 1
  }'
```

### DELETE - Eliminar jugador de partida
```bash
curl -X DELETE http://localhost:4000/matches/1/players/2
```

---

## 🏆 LOGROS

### GET - Listar todos los logros
```bash
curl http://localhost:4000/achievements
```

### GET - Obtener logro específico
```bash
curl http://localhost:4000/achievements/1
```

### POST - Crear nuevo logro
```bash
curl -X POST http://localhost:4000/achievements \
  -H "Content-Type: application/json" \
  -d '{
    "name": "Gran Maestro",
    "description": "Alcanzar ELO 2000"
  }'
```

### POST - Desbloquear logro para usuario
```bash
curl -X POST http://localhost:4000/users/1/achievements/3 \
  -H "Content-Type: application/json"
```

### GET - Obtener logros de usuario
```bash
curl http://localhost:4000/users/1/achievements
```

---

## 🔧 Uso con Variables

### Con jq (parsear JSON)
```bash
# Obtener solo el username
curl http://localhost:4000/users/1 | jq '.username'

# Obtener ELO del usuario
curl http://localhost:4000/users/1 | jq '.stats.elo'

# Listar solo nombres de amigos
curl http://localhost:4000/users/1/friends | jq '.[].username'
```

### Guardar en variable y usar
```bash
# Crear usuario y guardar ID
USER_ID=$(curl -s -X POST http://localhost:4000/users \
  -H "Content-Type: application/json" \
  -d '{
    "username": "test_user",
    "email": "test@test.com"
  }' | jq '.id')

echo "Usuario creado con ID: $USER_ID"

# Usar el ID para crear partida
curl http://localhost:4000/users/$USER_ID
```

### Crear script de prueba
```bash
#!/bin/bash

BASE_URL="http://localhost:4000"

# Listar usuarios
echo "=== Usuarios ==="
curl -s $BASE_URL/users | jq '.'

# Listar partidas
echo "=== Partidas ==="
curl -s $BASE_URL/matches | jq '.'

# Listar logros
echo "=== Logros ==="
curl -s $BASE_URL/achievements | jq '.'
```

---

## 🌐 En Postman

1. **Crear colección** con los endpoints base
2. **Variables de entorno**:
   - `BASE_URL` = `http://localhost:4000`
   - `USER_ID` = `1`
   - `MATCH_ID` = `1`

3. **Ejemplo de request**:
   - Method: GET
   - URL: `{{BASE_URL}}/users/{{USER_ID}}`
   - Headers: `Content-Type: application/json`

---

## 📝 Respuestas Comunes

### Éxito (200)
```json
{
  "id": 1,
  "username": "shadow_lord",
  "email": "shadow@transcendence.io",
  "createdAt": "2026-05-08T11:35:40.800Z"
}
```

### Creación exitosa (201)
```json
{
  "id": 6,
  "username": "nuevo_usuario",
  "email": "nuevo@test.com"
}
```

### Error - No encontrado (404)
```json
{
  "error": "Usuario no encontrado"
}
```

### Error - Validación (400)
```json
{
  "error": "username y email son requeridos"
}
```

### Error - Servidor (500)
```json
{
  "error": "Error al obtener usuario"
}
```

---

## 🚀 Script Completo de Prueba

Guarda como `test-api.sh`:

```bash
#!/bin/bash

BASE_URL="http://localhost:4000"
HEADER="Content-Type: application/json"

echo "🚀 Testing Transcendence API"
echo "========================================"

# Test 1: Health check
echo "✓ Health Check"
curl -s $BASE_URL/health | jq '.'
echo ""

# Test 2: Listar usuarios
echo "✓ Listar Usuarios"
curl -s $BASE_URL/users | jq '.' | head -30
echo ""

# Test 3: Obtener usuario
echo "✓ Usuario 1"
curl -s $BASE_URL/users/1 | jq '.username, .stats.elo'
echo ""

# Test 4: Listar partidas
echo "✓ Listar Partidas"
curl -s "$BASE_URL/matches?take=3" | jq '.' | head -20
echo ""

# Test 5: Listar logros
echo "✓ Listar Logros"
curl -s $BASE_URL/achievements | jq '.'
echo ""

echo "✅ Tests completados"
```

Ejecutar:
```bash
chmod +x test-api.sh
./test-api.sh
```
