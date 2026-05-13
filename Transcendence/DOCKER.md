# 🐳 Setup con Docker

## Quick Start

```bash
# Desde la raíz del proyecto
docker-compose up -d
```

El sistema levantará automáticamente:
- **PostgreSQL** en puerto 5432
- **Backend (Database)** en puerto 4000
- **Client** en puerto 80
- **Engine** (Game) en puerto 3000
- **Realtime** en puerto 42069
- **Redis** para comunicación

## Verificar Estado

```bash
# Ver logs
docker-compose logs -f database

# Ver estado de servicios
docker-compose ps

# Ejecutar comando en contenedor
docker-compose exec database npm run prisma studio
```

## Endpoints

```
GET  http://localhost:4000/users
GET  http://localhost:4000/feed
POST http://localhost:4000/signup
POST http://localhost:4000/post
```

## Desarrollo

### Con Docker
```bash
# Levantar solo database y postgres
docker-compose up database postgres

# Levantar todo
docker-compose up

# Parar
docker-compose down

# Limpiar volúmenes (reiniciar DB)
docker-compose down -v
```

### Local (sin Docker)
```bash
cd database
npm install
npm run prisma generate
npx prisma migrate dev --name init
npx prisma db seed
npm run dev
```

## Variables de Entorno

El archivo `.env` en la raíz controla:

```env
# PostgreSQL
POSTGRES_USER=transcendence
POSTGRES_PASSWORD=transcendence
POSTGRES_DB=transcendence

# Aplicación
PORT=4000
NODE_ENV=development
```

Para cambiar credenciales, edita el `.env` y ejecuta:
```bash
docker-compose down -v
docker-compose up
```

## Troubleshooting

### Puerto ya en uso
```bash
# Encontrar qué usa el puerto
lsof -i :4000

# Cambiar puerto en docker-compose.yml
# Cambiar: "4000:4000" por "8080:4000"
```

### Base de datos corrupta
```bash
# Reiniciar completamente
docker-compose down -v
docker-compose up --build
```

### Logs
```bash
docker-compose logs database  # Logs de la app
docker-compose logs postgres  # Logs de BD
docker-compose logs -f        # Todos los logs
```

## Producción

Para producción, ajusta:

1. `.env`:
```env
NODE_ENV=production
POSTGRES_PASSWORD=strong-password-here
```

2. `docker-compose.yml` - Descomenta `restart: always` en todos los servicios

3. Ejecuta:
```bash
docker-compose up -d
```
