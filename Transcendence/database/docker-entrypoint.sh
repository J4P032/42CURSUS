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

# Ejecutar migraciones
echo "📦 Ejecutando migraciones..."
npx prisma migrate deploy || echo "⚠️  Las migraciones ya están aplicadas"

# Ejecutar seed solo en desarrollo
if [ "$NODE_ENV" = "development" ]; then
  echo "🌱 Ejecutando seed..."
  npx prisma db seed || echo "⚠️  Seed ya ejecutado"
fi

echo "✅ Setup completado, iniciando servidor..."
echo "🔗 Servidor disponible en http://localhost:${PORT:-4000}"

# Iniciar la aplicación
exec npm run dev
