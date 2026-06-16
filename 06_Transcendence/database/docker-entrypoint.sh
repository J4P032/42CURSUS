#!/bin/sh

set -e

echo "🚀 Iniciando aplicación..."

# Esperar a que PostgreSQL esté disponible
echo "⏳ Esperando a que PostgreSQL esté disponible..."
MAX_RETRIES=30
RETRIES=0

while [ $RETRIES -lt $MAX_RETRIES ]; do
  if nc -z -w5 $DB_HOST $DB_PORT 2>/dev/null; then
    echo "✓ PostgreSQL disponible"
    break
  fi
  RETRIES=$((RETRIES + 1))
  echo "Intento $RETRIES/$MAX_RETRIES: PostgreSQL no disponible, esperando..."
  sleep 1
done

if [ $RETRIES -eq $MAX_RETRIES ]; then
  echo "❌ PostgreSQL no disponible después de $MAX_RETRIES intentos"
  exit 1
fi

echo "📦 Ejecutando migraciones..."
# Auto-baseline para bases de datos pre-existentes sin historial de Prisma
# (típicamente creadas por el antiguo `prisma db push`). En ese caso
# `migrate deploy` aborta con P3005; marcamos las migraciones como aplicadas
# y reintentamos. Otros fallos se propagan tal cual.
DEPLOY_OUTPUT=$(npx prisma migrate deploy 2>&1) || DEPLOY_RC=$?
echo "$DEPLOY_OUTPUT"

if [ -n "${DEPLOY_RC:-}" ]; then
  if echo "$DEPLOY_OUTPUT" | grep -q "P3005"; then
    echo "🩹 Esquema existente sin historial de migraciones; aplicando baseline..."
    for migration_dir in prisma/migrations/*/; do
      [ -d "$migration_dir" ] || continue
      migration_name=$(basename "$migration_dir")
      npx prisma migrate resolve --applied "$migration_name"
    done
    echo "↻ Reintentando migraciones..."
    npx prisma migrate deploy
  else
    exit "$DEPLOY_RC"
  fi
fi

# Ejecutar seed solo en desarrollo
if [ "$NODE_ENV" = "development" ]; then
  echo "🌱 Ejecutando seed..."
  npx prisma db seed || echo "⚠️  Seed ya ejecutado"
fi

echo "✅ Setup completado, iniciando servidor..."
echo "🔗 Servidor disponible en http://localhost:${PORT:-4000}"

# Iniciar la aplicación
exec npm run dev
