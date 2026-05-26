#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <stdio.h>

typedef struct	s_client{
	int		id;
	char	RBUFFER[600000];
	int		index;
	///
} t_client;

t_client			clientes[1024];
char				BUFF[600000];
char*				ARGS = "Wrong number of arguments\n";
char*				FATAL = "Fatal error\n";
int					sockfd, connfd, max_fd;
int					id = 0;
socklen_t			len;
fd_set				fds, rfds; ///
struct sockaddr_in	servaddr, cli; 

void	ft_error(char* str){
	write(2, str, strlen(str));
	for (int i = 0; i < 1024; i++){
		if (FD_ISSET(i, &fds))
			close(i);
	}
	exit(1);
}


void	broadcast(int fd, char* str){
	for(int i = 0; i <= max_fd; i++){
		if (FD_ISSET(i, &fds) && i != sockfd && i != fd){
			send(i, str, strlen(str), 0);
			///
		}
	}
}

void	join_client(int fd){
	FD_SET(fd, &fds); //unir fd al set fds
	clientes[fd].id = id++; //actualizar id
	if (fd > max_fd) //actualizar max_fd
		max_fd = fd;
	char	buf[100];
	sprintf(buf, "server: client %d just arrived\n", clientes[fd].id);
	broadcast(fd, buf); //componer buf y mandar
	clientes[fd].index = 0; //importantisimo iniciarlizarlo a cero
}


void	remove_client(int fd){
	
	//cerrar el fd
	FD_CLR(fd, &fds); //quitar fd del fds
	char	buf[100];
	sprintf(buf, "server: client %d just left\n", clientes[fd].id); //componer el buf y mandarlo
	broadcast(fd, buf);
	clientes[fd].id = -1; //resetear id a -1
	if (fd == max_fd){ //actualizar el max_fd
		int	next_maxfd = sockfd;
		for (int i = 0; i <= max_fd; i++){
			if (FD_ISSET(i, &fds) && i > next_maxfd)
				next_maxfd = i;
		}
		max_fd = next_maxfd;
	}
	bzero(clientes[fd].RBUFFER, strlen(clientes[fd].RBUFFER));
	///
	close(fd);
}



void	miniserv(void){
	FD_ZERO(&fds);
	FD_SET(sockfd, &fds);
	max_fd = sockfd;
	while (1){
		rfds = fds;
		///
		if (select(max_fd + 1, &rfds, NULL, NULL, NULL) < 0) ///
			ft_error(FATAL);
		for (int fd = 0; fd <= max_fd; fd++){
			//read rfds
			if (FD_ISSET(fd, &rfds)){
				if (fd == sockfd){ //cliente nuevo
					len = sizeof(cli);
					connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
					if (connfd >= 1024){
						close(connfd);
					} else if (connfd >= 0) { 
						join_client(connfd);
						break ;
					}
					else
						ft_error(FATAL);
				}
				else{ //ya estaba el cliente
					bzero(BUFF, 600000);
					int n = recv(fd, BUFF, 599999, 0);
					if (n <= 0){ //cliente quit
						remove_client(fd);
						break ;
					}
					if (n > 0){ //manda mensaje
						//NO SE DEBE INICIALIZAR A CERO EL .index AQUI YA QUE PUEDE LLEGAR POR TROZOS Y TRUNCARIA
						for (int i = 0; i < n; i++){
							clientes[fd].RBUFFER[clientes[fd].index++] = BUFF[i];
							if (BUFF[i] == '\n'){
								clientes[fd].RBUFFER[clientes[fd].index] = '\0';
								char prefix[100];
                                sprintf(prefix, "client %d: ", clientes[fd].id);
                                broadcast(fd, prefix);
                                broadcast(fd, clientes[fd].RBUFFER);
								clientes[fd].index = 0;
							}
						}
					}
				}
			}
			//write wfds
			///
		}
	}
}


int		main(int argc, char **argv) {

	if (argc != 2)
		ft_error(ARGS);

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
	return(0);
}