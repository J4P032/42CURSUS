# Endpoints REST

Para conectarse con la base de datos postgresql se realiza mediante REST API con prisma + express
Las respuestas que se obtienen son en formato JSON


# Estado del servicio
curl http://localhost:${PORT}/health

# Listar usuarios
curl http://localhost:4000/users

# Obtener usuario específico
curl http://localhost:4000/users/1

# Crear nuevo usuario
curl -X POST http://localhost:4000/users \
  -H "Content-Type: application/json" \
  -d '{"username":"test","email":"test@test.com"}'

# Listar partidas
curl http://localhost:4000/matches

# Agregar jugador a partida
curl -X POST http://localhost:4000/matches/1/players/2

# Listar logros del usuario
curl http://localhost:4000/users/1/achievements