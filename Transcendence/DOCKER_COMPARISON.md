# 📋 Comparación: Local vs Docker

## ✅ Ventajas de Docker

| Aspecto | Local | Docker |
|---------|-------|--------|
| **Setup** | Manual (7+ pasos) | Automatizado (1 comando) |
| **Dependencias** | Instalar localmente | Incluidas en imagen |
| **PostgreSQL** | Instalar y configurar | Automático |
| **Consistencia** | Puede variar por OS | Igual en todos lados |
| **Producción** | Requiere reconfiguración | Listo para usar |
| **Equipo** | Cada uno configura | Mismo para todos |
| **Limpieza** | Dejar archivos dispersos | Eliminar imágenes/volúmenes |

## 🚀 Instalación Rápida

### Opción 1: Docker (Recomendado)
```bash
docker-compose up -d
# Servidor en http://localhost:4000
```

### Opción 2: Local
```bash
cd database
npm install
npx prisma migrate dev --name init
npx prisma db seed
npm run dev
# Servidor en http://localhost:4000
```

## 📁 Estructura

```
42-ft_transcendence/
├── docker-compose.yml     ← Orquestación de servicios
├── .env                   ← Variables (compartidas)
├── database/
│   ├── Dockerfile         ← Imagen de la app
│   ├── docker-entrypoint.sh  ← Script de inicio
│   ├── .dockerignore      ← Archivos a ignorar
│   ├── src/
│   ├── prisma/
│   └── package.json
├── postgres/              ← Volumen de datos
└── ...
```

## 🔧 Configuración

### Variables de entorno (.env)

```env
# Base de datos (compartida entre servicios)
POSTGRES_USER=transcendence
POSTGRES_PASSWORD=transcendence
POSTGRES_DB=transcendence
```

### Puertos

| Servicio | Puerto | Acceso |
|----------|--------|--------|
| Backend | 4000 | http://localhost:4000 |
| PostgreSQL | 5432 | localhost:5432 |
| Engine | 3000 | http://localhost:3000 |
| Realtime | 42069 | ws://localhost:42069 |
| Client | 80 | http://localhost |
| Redis | 6379 | localhost:6379 |

## 📊 Automatización con Docker

El Dockerfile y docker-entrypoint.sh automatizan:

✅ Generar cliente Prisma  
✅ Ejecutar migraciones  
✅ Popular base de datos (seed)  
✅ Health checks  
✅ Reintentos de conexión a BD  

## 💡 Comandos Útiles

```bash
# Inicio/Parada
docker-compose up -d        # Iniciar en background
docker-compose down         # Parar servicios
docker-compose restart      # Reiniciar
docker-compose down -v      # Parar + eliminar volúmenes

# Desarrollo
docker-compose logs -f database           # Ver logs en vivo
docker-compose exec database npm run prisma studio  # Abrir Prisma Studio
docker-compose exec database npm run prisma db push # Sync schema

# Rebuild
docker-compose build --no-cache database  # Reconstruir imagen
docker-compose up --build                # Up + build

# Testing
docker-compose ps                        # Estado de servicios
docker-compose exec database npm test    # Ejecutar tests
```

## 🛡️ Seguridad

### Desarrollo
```env
POSTGRES_PASSWORD=transcendence  ← Simple, solo desarrollo
NODE_ENV=development
```

### Producción
```env
POSTGRES_PASSWORD=super-long-random-password-here
NODE_ENV=production
```

## 🔄 Flujo de Desarrollo

1. Editar código localmente
2. Si cambias schema.prisma:
   ```bash
   docker-compose restart database
   ```
3. Si cambias dependencias:
   ```bash
   docker-compose down
   docker-compose build --no-cache database
   docker-compose up
   ```
4. Si quieres limpiar todo:
   ```bash
   docker-compose down -v
   docker-compose up --build
   ```
