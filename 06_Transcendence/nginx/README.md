# Nginx

The **Nginx** service provides a reverse proxy and load balancer for the transcendence application, handling HTTPS termination, request routing, and static file serving.

## Overview

Nginx acts as the entry point for all client requests, forwarding them to appropriate backend services while managing:
- **SSL/TLS Termination**: Self-signed certificate generation and HTTPS handling
- **Reverse Proxying**: Routes requests to the Prisma application
- **Load Balancing**: Distributes traffic across backend services
- **Static Assets**: Serves pre-compressed and cached assets
- **Health Checks**: Monitors service availability

## Architecture

```
nginx/
├── Dockerfile # Alpine-based Nginx container image
├── docker-entrypoint.sh # Startup script for SSL cert generation
└── nginx.conf # Nginx configuration template
```

## Configuration

### Docker Entrypoint (`docker-entrypoint.sh`)

The entrypoint script handles:
1. **Certificate Generation**: Creates self-signed SSL certificates if not present
   - Location: `/etc/nginx/certs/`
   - Validity: 365 days
   - CN: localhost (for dev/testing)

2. **Configuration Templating**: Uses `envsubst` to render `nginx.conf.template`
   - Substitutes environment variables (e.g., `PRISMA_PORT`)
   - Preserves Nginx variables (e.g., `$host`, `$remote_addr`)

3. **Service Startup**: Launches Nginx in foreground mode

### Nginx Configuration (`nginx.conf`)

Key features:
- **HTTP -> HTTPS Redirect**: All HTTP traffic redirected to HTTPS
- **Proxy Pass**: Routes requests to backend services
- **Upstream Definition**: Configurable backend service addresses
- **Health Monitoring**: Regular health checks on backend endpoints

Example routing:
http://nginx:80 -> HTTPS redirect https://nginx:443 -> Proxied to Prisma backend

## Environment Variables

```env
PRISMA_PORT=4000           # Backend service port (default: 4000)
```

## SSL Certificates

### Self-Signed Certificates (Development)

Certificates are auto-generated on first run:

/etc/nginx/certs/certificate.crt
/etc/nginx/certs/private.key

### Production Certificates
For production deployments, mount external certificates:

```bash
docker run -v /path/to/certs:/etc/nginx/certs:ro ...
```

## Running the Service

### Docker

```bash
# Build image
docker build -t transcendence-nginx .

# Run container
docker run -d \
  --name nginx \
  -p 80:80 \
  -p 443:443 \
  -e PRISMA_PORT=4000 \
  transcendence-nginx
```

### Docker Compose

```YAML
services:
  nginx:
    build: ./nginx
    ports:
      - "80:80"
      - "443:443"
    environment:
      PRISMA_PORT: 4000
    depends_on:
      - prisma  # Backend service
```

## Health Checks

Nginx includes a built-in health check:

- **Interval**: 30 seconds
- **Timeout**: 10 seconds
- **Start Period**: 5 seconds (grace period)
- **Retries**: 3 failures before unhealthy

Check health:

```bash
docker exec nginx wget --quiet --tries=1 --spider https://localhost/ || echo "Unhealthy"
```

## Logs
```bash
# View access logs
docker exec nginx tail -f /var/log/nginx/access.log

# View error logs
docker exec nginx tail -f /var/log/nginx/error.log
```

## Troubleshooting

### Certificate Issues

```bash
# Verify certificate validity
openssl x509 -in /etc/nginx/certs/certificate.crt -text -noout

# Regenerate certificates (remove existing first)
rm /etc/nginx/certs/*
docker restart nginx
```

### Connection Issues

```bash
# Test connectivity to backend
docker exec nginx curl -v http://prisma:4000/health

# Check Nginx configuration
docker exec nginx nginx -t
```

### Port Conflicts

If ports 80/443 are in use:

```bash
docker run -p 8080:80 -p 8443:443 ...
```

### Performance Tuning

The provided configuration includes optimizations for:

- Connection pooling
- Gzip compression
- Caching headers
- Buffer sizing

For high-traffic deployments, consider:

- Increasing worker_processes (auto-detect or set explicitly)
- Tuning keepalive_timeout
- Enabling upstream least_conn for load balancing

## Related Documentation
/client/README.md - Great Risk client and game mechanics
/database/README.md - Database and REST API
/engine/README.md - Engine Service - Game state publisher
/realtime/README.md - Realtime Service - WebSocket connection handler
/README.md - Global project readme