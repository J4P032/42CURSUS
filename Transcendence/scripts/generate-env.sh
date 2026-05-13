#!/bin/bash

# Script para generar database/.env desde el .env raíz
# Uso: ./scripts/generate-env.sh

set -e

# Colores para output
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Archivo raíz .env
ROOT_ENV=".env"
DB_ENV="database/.env"

# Verificar que existe el .env raíz
if [ ! -f "$ROOT_ENV" ]; then
    echo -e "${YELLOW}Error: No se encontró $ROOT_ENV${NC}"
    exit 1
fi

# Cargar variables del .env raíz
export $(cat "$ROOT_ENV" | grep -v '^#' | xargs)

# Valores por defecto si no existen
POSTGRES_USER=${POSTGRES_USER:-transcendence}
POSTGRES_PASSWORD=${POSTGRES_PASSWORD:-transcendence}
POSTGRES_DB=${POSTGRES_DB:-transcendence}
POSTGRES_HOST=${POSTGRES_HOST:-localhost}
POSTGRES_PORT=${POSTGRES_PORT:-5432}
DB_PORT=${DB_PORT:-4000}

# Construir DATABASE_URL
DATABASE_URL="postgresql://${POSTGRES_USER}:${POSTGRES_PASSWORD}@${POSTGRES_HOST}:${POSTGRES_PORT}/${POSTGRES_DB}"

# Generar database/.env
cat > "$DB_ENV" << EOF
# Generado automáticamente desde .env raíz
# NO editar manualmente - cambiar .env raíz en su lugar
DATABASE_URL="$DATABASE_URL"
PORT=$DB_PORT
EOF

echo -e "${GREEN}✓ Archivo generado: $DB_ENV${NC}"
echo -e "${BLUE}DATABASE_URL: $DATABASE_URL${NC}"
echo -e "${BLUE}PORT: $DB_PORT${NC}"
