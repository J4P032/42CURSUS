# Build stage
FROM node:20-alpine AS builder

WORKDIR /app

# Instalar dependencias del sistema necesarias
RUN apk add --no-cache openssl

# Copiar archivos de configuración
COPY package.json package-lock.json* ./
COPY prisma.config.ts ./
COPY tsconfig.json ./

# Instalar dependencias
RUN npm ci

# Copiar el código fuente
COPY prisma ./prisma
COPY src ./src

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

# Copiar archivos de configuración
COPY package.json package-lock.json* ./
COPY prisma.config.ts ./
COPY tsconfig.json ./

# Variables de entorno por defecto
ENV NODE_ENV=production
ENV PORT=${PRISMA_PORT:-4000}

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=40s --retries=3 \
    CMD curl -f http://localhost:${PRISMA_PORT:-4000}/health || exit 1

# Copiar script de entrada
COPY docker-entrypoint.sh ./
RUN chmod +x ./docker-entrypoint.sh

# Exponer puerto
EXPOSE ${PRISMA_PORT:-4000}

# Ejecutar script de entrada
ENTRYPOINT ["./docker-entrypoint.sh"]
