#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <stdio.h>

typedef struct s_clients{
	int	id;
	char* msg;
} t_clients;

char* args = "Wrong number of arguments\n";
char* fatal = "Fatal error\n";
int	sockfd, connfd;
struct sockaddr_in	servaddr, cli; 
socklen_t	len;
fd_set	fds, rfds;
int	max_fd = 0, id = 0;
t_clients	clientes[4000];
//char	total_msg[600020];

void ft_error(char* str){
	write(2, str, strlen(str));
	for (int i = 0; i <= max_fd; i++){
		if (clientes[i].msg != NULL){
			free(clientes[i].msg);
			clientes[i].msg = NULL;
		}
		if (FD_ISSET(i, &fds))
			close(i);
	}
	exit(1);
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
		ft_error(fatal);
	newbuf[0] = 0;
	if (buf != 0)
		strcat(newbuf, buf);
	free(buf);
	strcat(newbuf, add);
	return (newbuf);
}

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
				ft_error(fatal);
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

void	broadcast_msg(int fd, char* line){
	for (int i = 0; i <= max_fd; i++){
		if (clientes[i].id != -1 && i != sockfd && i != fd)
			send(i, line, strlen(line), 0);
	}
}


void	join_client(int fd){
	FD_SET(fd, &fds);
	if (fd > max_fd)
		max_fd = fd;
	clientes[fd].id = id++;
	char buf[100];
	sprintf(buf, "server: client %d just arrived\n", clientes[fd].id);
	broadcast_msg(fd, buf);
}

void	leave_client(int fd){
	FD_CLR(fd, &fds);
	char buf[100];
	sprintf(buf, "server: client %d just left\n", clientes[fd].id);
	broadcast_msg(fd, buf);
	if (fd == max_fd){
		int next_fdmax = 0; 
		for (int i = 0; i < max_fd; i++){
			if (FD_ISSET(i, &fds) && i > next_fdmax)
				next_fdmax = i;
		}
		max_fd = next_fdmax;
	}
	if (clientes[fd].msg){
		free(clientes[fd].msg);
		clientes[fd].msg = NULL;
	}
	clientes[fd].id = -1;
	close(fd);	
}


void	miniserver(){
	FD_ZERO(&fds);
	FD_SET(sockfd, &fds);
	max_fd = sockfd; //el valor maximo
	while(1){
		rfds = fds;
		
		if (select(max_fd + 1, &rfds, NULL, NULL, NULL) < 0)
			ft_error(fatal);
		for (int i = 0; i <= max_fd; i++){
			if (!FD_ISSET(i, &rfds))
				continue;
			if (i == sockfd){
				len = sizeof(cli);
				connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
				if (connfd >= 1024){
					close(connfd);
				} else if (connfd >= 0){
					join_client(connfd);
					break ;
				}
				else
					ft_error(fatal);
			}
			else{ //otro cliente ya conectado
				char buff[4097];
				int n = recv(i, buff, 4096, 0);
				if (n <= 0)
					leave_client(i);
				if (n > 0){
					buff[n] = '\0';
					clientes[i].msg = str_join(clientes[i].msg, buff);
					char*	line = NULL;
					char	prefix[100]; //para evitar el global de total_msg[600020]
					while (extract_message(&clientes[i].msg, &line)){
						/*es mas elegante con strlen(line) + 50, pero podria producir un buffer overflow si el mensaje es muy largo, asi que lo hago con malloc
						debido a que al no ser la variable global la memoria se reserva en el stack que hay menos que en el heap (globales)*/
						//char total_msg[strlen(line) + 50];
						//total_msg al ser ahora reservado en el global, no habría problemas.
						//antes lo hacia con reserva global de total_msg[600020] pero lo que pongo ahora es mucho mejor 
						//sprintf(total_msg, "client %d: %s", clientes[i].id, line);
						sprintf(prefix, "client %d: ", clientes[i].id);
						broadcast_msg(i, prefix);
						broadcast_msg(i, line); //asi nunca se queda sin memoria al poner dos veces el broadcast.
						free(line);
						line = NULL; 
					}
				}
			}
		}
	}
}


int	main(int ac, char** av){
	if (ac != 2)
		ft_error(args);

	for (int i = 0; i < 4000; i++){
		clientes[i].id = -1;
		clientes[i].msg = NULL;
	}

	// socket create and verification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1)
		ft_error(fatal);
	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(atoi(av[1])); 
  
	// Binding newly created socket to given IP and verification 
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) == -1)
		ft_error(fatal);
	if (listen(sockfd, 10) == -1)
		ft_error(fatal);
	
	miniserver();
	return 0;
}
