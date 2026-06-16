# Build stage
FROM node:20-alpine AS builder

WORKDIR /app

# Instalar dependencias del sistema necesarias
RUN apk add --no-cache openssl

# Copiar archivos de configuración (build context = repo root)
COPY database/package.json database/package-lock.json* ./
COPY database/prisma.config.ts ./
COPY database/tsconfig.json ./

# Instalar dependencias
RUN npm ci

# Copiar el código fuente y el paquete shared (para seed de achievements)
COPY database/prisma ./prisma
COPY database/src ./src
COPY shared ./shared

# Generar cliente Prisma (usar URL dummy para el build)
ENV DATABASE_URL="postgresql://user:password@localhost:5432/dummy"
RUN npx prisma generate

# Production stage
FROM node:20-alpine

WORKDIR /app

# Instalar curl para health checks y openssl
RUN apk add --no-cache curl openssl netcat-openbsd

# Copiar node_modules del builder
COPY --from=builder /app/node_modules ./node_modules
COPY --from=builder /app/prisma ./prisma
COPY --from=builder /app/src ./src
COPY --from=builder /app/shared ./shared

# Copiar archivos de configuración
COPY database/package.json database/package-lock.json* ./
COPY database/prisma.config.ts ./
COPY database/tsconfig.json ./

# Variables de entorno por defecto
ENV NODE_ENV=production
ENV PORT=${PRISMA_PORT:-4000}

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=40s --retries=3 \
    CMD curl -f http://localhost:${PRISMA_PORT:-4000}/health || exit 1

# Copiar script de entrada
COPY database/docker-entrypoint.sh ./
RUN chmod +x ./docker-entrypoint.sh

# Exponer puerto
EXPOSE ${PRISMA_PORT:-4000}

# Ejecutar script de entrada
ENTRYPOINT ["./docker-entrypoint.sh"]
