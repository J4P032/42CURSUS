# User Documentation

## Provided Services
This infrastructure provides a web hosting stack composed of:
- **Nginx**: A web server configured with HTTPS/TLS.
- **WordPress**: A content management system (CMS).
- **MariaDB**: A relational database to store WordPress data.

## Managing the Project
- **Start**: Run `make` or `make up` in the terminal from the project root.
- **Stop**: Run `make down` to stop the services without deleting data.
- **Restart**: Run `make restart` to stop and start the services again.
- **clean**: Run `make fclean` to stop and remove all services plus remove of volumes and custom local data storage.


## Accessing the Website
- **Public Site**: Open a web browser and go to `https://jrollon-.42.fr`. To check no 80 port is listen `http://jrollon-.42.fr` in terminal run: 
```bash
curl -I http://jrollon-.42.fr" or "docker port nginx
```
that would give us an error. Or:
```bash
docker port nginx
```
- **Admin Panel**: Access the WordPress dashboard at `https://jrollon-.42.fr/wp-admin`.

## Managing Credentials
Credentials (usernames, passwords, and database names) are not stored in the repository for security. They are located in the `.env` file within the `srcs/` directory. You can modify this file before the first launch to set your preferred passwords.

## Checking Service Status
To verify that all services are running correctly, use the following command:
```bash
docker ps
```
All containers (`nginx`, `wordpress`, `mariadb`) should have a status of "Up".

## Checking SSL use and wordpress as (WP-CLI)
To verify that certificates are signed run:
```bash
openssl s_client -connect localhost:443 -tls1_3
```
to demostrate that wordpress is configured run:
```bash
docker exec wordpress wp user list --allow-root
```

