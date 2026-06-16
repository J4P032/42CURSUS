# ============ PHASE 1: BUILD ============
FROM node:20-alpine AS builder

ARG VITE_API_URL=https://localhost/api/engine
ARG VITE_WS_URL=wss://localhost/ws
ENV VITE_API_URL=$VITE_API_URL
ENV VITE_WS_URL=$VITE_WS_URL

WORKDIR /app

# Build context is the repo root so we can resolve workspace deps.
COPY package.json package-lock.json* ./
COPY shared ./shared
COPY client ./client

RUN npm install --workspaces --include-workspace-root
RUN npm run build -w client

# ============ PHASE 2: PRODUCTION ============
FROM nginx:alpine
COPY --from=builder /app/client/dist /usr/share/nginx/html
EXPOSE 80
CMD ["nginx", "-g", "daemon off;"]
