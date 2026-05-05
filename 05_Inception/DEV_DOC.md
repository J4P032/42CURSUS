# Developer Documentation

## Environment Setup
### Prerequisites
- Operating System: Linux (Debian/Ubuntu recommended).
- Docker and Docker Compose installed.
- Local Domain: Add `127.0.0.1 jrollon-.42.fr` to your `/etc/hosts` file.

### Configuration Files
- **srcs/docker-compose.yml**: Orchestrates the service containers.
- **srcs/.env**: Contains secrets and environment variables. **Must be created manually.**

## Build and Launch
The project is managed through a Makefile at the root:
- `make`: Builds the images and starts the containers in detached mode.
- `make build`: Specifically triggers the building of Docker images.
- `make down`: Stops and removes the containers.
- `make fclean`: Removes containers, images, networks, and all persistent data.

## Management Commands
- **Check Logs**: `docker logs <container_name>` (e.g., `docker logs mariadb`).
- **Access Container Shell**: `docker exec -it <container_name> sh`.
- **List Volumes**: `docker volume ls`.

## Data Persistence and Storage
Data persists even when containers are deleted. The data is stored on the host machine in the following directories:
- **MariaDB Data**: `/home/jrollon-/data/mariadb`
- **WordPress Data**: `/home/jrollon-/data/wordpress`

These paths are mapped as Docker Volumes in the `docker-compose.yml` file to ensure that website content and database records are not lost between restarts.
