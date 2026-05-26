#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/select.h>

typedef struct s_client{
	int		id;
	char*	rbuffer;
    char*   wbuffer;	
} t_client;


t_client			clientes[4000];
char*				ARGS = "Wrong number of arguments\n";
char*				FATAL = "Fatal error\n";
int					sockfd, connfd, max_fd;
int					id = 0;
socklen_t			len;
struct sockaddr_in	servaddr, cli;
fd_set				fds, rfds, wfds;

void	ft_error(char* str){
	write(2, str, strlen(str));
	for (int i = 0; i < 4000; i++){
		if (clientes[i].rbuffer){
			free(clientes[i].rbuffer);
			clientes[i].rbuffer = NULL;
		}
        if (clientes[i].wbuffer){
			free(clientes[i].wbuffer);
			clientes[i].wbuffer = NULL;
		}
		if (FD_ISSET(i, &fds))
			close(i);
	}
	exit(1);
}

// Extracts newline from buf to msg and moves the buf
int extract_message(char **buf, char **msg)
{
	char	*newbuf;
	int	i;

	*msg = 0;
	if (*buf == 0)
		return (0);
	i = 0;
	while ((*buf)[i])
	{
		if ((*buf)[i] == '\n')
		{
			newbuf = calloc(1, sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
			if (newbuf == 0)
				ft_error(FATAL);
			strcpy(newbuf, *buf + i + 1);
			*msg = *buf;
			(*msg)[i + 1] = 0;
			*buf = newbuf;
			return (1);
		}
		i++;
	}
	return (0);
}

char *str_join(char *buf, char *add)
{
	char	*newbuf;
	int		len;

	if (buf == 0)
		len = 0;
	else
		len = strlen(buf);
	newbuf = malloc(sizeof(*newbuf) * (len + strlen(add) + 1));
	if (newbuf == 0)
		ft_error(FATAL);
	newbuf[0] = 0;
	if (buf != 0)
		strcat(newbuf, buf);
	free(buf);
	strcat(newbuf, add);
	return (newbuf);
}

void	broadcast(int fd, char* str){
	for (int i = 0; i <= max_fd; i++){
		if (FD_ISSET(i, &fds) && i != sockfd && i != fd){
			clientes[i].wbuffer = str_join(clientes[i].wbuffer, str);
            //send(i, str, strlen(str), 0);
		}
	}
}

void	join_client(int fd){
	FD_SET(fd, &fds); //meter el fd en el set
	clientes[fd].id = id++; //actualizar el id
	if (fd > max_fd) //actualizar el max_fd
		max_fd = fd;
	char buf[100];
	sprintf(buf, "server: client %d just arrived\n", clientes[fd].id);
	broadcast(fd, buf);//componer el buf y mandarlo
}

void	remove_client(int fd){
	FD_CLR(fd, &fds); //quitar el fd del set
	char buf[100];
	sprintf(buf, "server: client %d just left\n", clientes[fd].id);
	broadcast(fd, buf); //componer el buf y mandarlo
	clientes[fd].id = -1; //resetear el id al -1
	if (fd == max_fd){ 
		int next_maxfd = sockfd;
		for (int i = 0; i <= max_fd; i++){
			if (FD_ISSET(i, &fds) && i > next_maxfd)
				next_maxfd = i;
		}
		max_fd = next_maxfd; //actualizar el max_fd
	}
	if (clientes[fd].rbuffer){
		free(clientes[fd].rbuffer); //liberar memorias rbuffer
		clientes[fd].rbuffer = NULL;
    }
    if (clientes[fd].wbuffer){
		free(clientes[fd].wbuffer); //liberar memorias wbuffer
		clientes[fd].wbuffer = NULL;
    }
	close (fd); //cerrar el fd
}

void	miniserv(void){
	FD_ZERO(&fds);
	FD_SET(sockfd, &fds);
	max_fd = sockfd;
	while (1){
		rfds = fds;
        wfds = fds;
		if (select(max_fd + 1, &rfds, &wfds, NULL, NULL) < 0)
			ft_error(FATAL);
		for (int fd = 0; fd <= max_fd; fd++){
			//lectura
			if (FD_ISSET(fd, &rfds)){
				if (fd == sockfd){ //nuevo cliente
					len = sizeof(cli);
					connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
					if (connfd >= 1024){
						close(connfd);
					}
					else if (connfd >= 0) { 
						join_client(connfd);
						break ;
					}
					else
						ft_error(FATAL);
				}
				else{ //cliente ya conectado
					char BUFF[4097];
					int n = recv(fd, BUFF, 4096, 0);
					if (n <= 0){	//desconectar cliente
						remove_client(fd);
						break ;
					}
					if (n > 0){ //mandar msg
						BUFF[n] = '\0';
						clientes[fd].rbuffer = str_join(clientes[fd].rbuffer, BUFF);
						char* line = NULL;
						while (extract_message(&clientes[fd].rbuffer, &line)){
							char prefix[100];
							sprintf(prefix, "client %d: ", clientes[fd].id);
							broadcast(fd, prefix);
							broadcast(fd, line);
							free(line);
							line = NULL;
						}
					}
				}
			}
			//escritura con wfds
            if (FD_ISSET(fd, &wfds) && clientes[fd].wbuffer){
                send(fd, clientes[fd].wbuffer, strlen(clientes[fd].wbuffer), 0);
                free(clientes[fd].wbuffer);
                clientes[fd].wbuffer = NULL;
            }
		}
	}
}


int		main(int argc, char **argv) {

	if (argc != 2)
		ft_error(ARGS);

	//init struct
	for (int i = 0; i < 4000; i++){
		clientes[i].id = -1;
		clientes[i].rbuffer = NULL;
        clientes[i].wbuffer = NULL;
	}

	// socket create and verification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1)
		ft_error(FATAL);
	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(atoi(argv[1])); 
  
	// Binding newly created socket to given IP and verification 
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) == -1)
		ft_error(FATAL);
	if (listen(sockfd, 128) == -1)
		ft_error(FATAL);


	miniserv();
	return (0);
}