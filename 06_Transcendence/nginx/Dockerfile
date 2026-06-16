FROM nginx:1.25-alpine

# Install OpenSSL (for self-signed cert) and gettext (for envsubst)
RUN apk add --no-cache openssl gettext

# Copy configuration template (rendered by entrypoint via envsubst)
COPY nginx.conf /etc/nginx/nginx.conf.template

# Copy entrypoint script
COPY docker-entrypoint.sh /docker-entrypoint.sh
RUN chmod +x /docker-entrypoint.sh

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD wget --quiet --tries=1 --spider https://localhost/ || exit 1

EXPOSE 80 443

ENTRYPOINT ["/docker-entrypoint.sh"]