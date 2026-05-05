*This project has been created as part of the 42 curriculum by jrollon-.*

# Inception

## Description
The Inception project consists of designing a complete system infrastructure using Docker. The main goal is to set up a small infrastructure composed of several services (Nginx, MariaDB, and WordPress) running in separate containers, interconnected through a dedicated Docker network and using persistent volumes. This project focuses on virtualization, containers groups, and system administration.

## Instructions
1. **Prerequisites**: Ensure `docker` and `docker-compose` are installed on your host.
2. **Setup**: Create a `.env` file in the `srcs/` directory with the required credentials with this information:

```bash
DOMAIN_NAME=jrollon-.42.fr
SQL_DATABASE=wordpress
SQL_USER=(your user name)
SQL_PASSWORD=xxxx
SQL_ROOT_PASSWORD=xxxx
SITE_TITLE=Inception_Project
ADMIN_USER=(anything without 'admin' in it)
WP_ADMIN_PASSWORD=xxxx
WP_ADMIN_EMAIL=(valid email)
USER_LOGIN=(user name)
USER_PASSWORD=xxx
USER_EMAIL=(valid email)
```


3. **Compilation**: Run `make` at the root of the repository. This will build the images and launch the containers.
4. **Execution**: The services will be accessible at `https://jrollon-.42.fr`.

## Resources
- [Docker Documentation](https://docs.docker.com/)
- [MariaDB Knowledge Base](https://mariadb.com/kb/en/)
- [WordPress CLI Handbook](https://make.wordpress.org/cli/handbook/)
- [Nginx SSL Module Configuration](https://nginx.org/en/docs/http/ngx_http_ssl_module.html)

### AI Usage Disclosure
Artificial Intelligence (GitHub Copilot) was used during this project for the following tasks:
- Explaining technical concepts
- Debugging shell scripts for MariaDB and WordPress init.
- Formatting MD files.
- Understand how to configure Makefile.

## Project Description
This project utilizes Docker to put services into containers, ensuring isolation. Each service is built from a custom Dockerfile based on Debian Bookworm, avoiding pre-made images from Docker Hub.

### Design Choices
- **Debian Bookworm**: Chosen as the base OS for all images to ensure stability and be lightweight. Has to be the penultimate version of debian at the moment of making Inception.
- **TLS 1.3**: Implemented in Nginx to meet modern security standards.
- **WP-CLI**: Automated WordPress installation and user management.

### Technical Comparisons
- **Virtual Machines vs Docker**: Virtual Machines (VMs) virtualize hardware and include a full OS, leading to high resource consumption and slow boot times. Docker virtualizes the OS kernel, sharing it with the host, which makes containers significantly lighter, faster, and more efficient.
- **Secrets vs Environment Variables**: Environment Variables are easy to use but can be exposed in process lists or logs. Secrets (like Docker Secrets) are specifically designed to store sensitive data (passwords, keys) more securely. Not used in this project.
- **Docker Network vs Host Network**: A Docker Network provides an isolated virtual network where containers communicate using internal IPs or service names. The Host Network removes isolation, making the container share the host's IP and ports directly, which is less secure and can lead to port conflicts.
- **Docker Volumes vs Bind Mounts**: Docker Volumes are managed entirely by Docker and stored in a protected area of the host filesystem, making them more portable and secure. Bind Mounts link a specific path on the host to a path in the container, depending on the host's directory structure.
I use Bind Mounts (but declared as named volumes) to ensure the subject that has to save data in specific route (/home/jrollon-/data/)
