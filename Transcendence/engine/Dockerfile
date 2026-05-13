FROM node:20-alpine

WORKDIR /app

# npm workspaces requires every declared workspace's package.json to exist
# at install time, even when scoping with -w. Copy stubs for the ones we
# don't need at runtime; only engine + shared bring code along.
COPY package.json package-lock.json* ./
COPY shared ./shared
COPY engine ./engine
COPY client/package.json ./client/package.json

RUN npm install -w engine --omit=dev

EXPOSE 3000

CMD ["node", "engine/src/index.js"]
