/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 14:28:42 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/04 11:07:17 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# include <signal.h>
# include <sys/types.h>
# include "./ft_printf/ft_printf.h"
# include "./libft/libft.h"

# define B_0 SIGUSR1
# define B_1 SIGUSR2
# define RECEIVE_HDR 0
# define RECEIVE_FORMULA 1
# define RECEIVE_MSG 2
# define MSG_RECEIVED 3
# define MSG_PRINTED 4

typedef struct s_client
{
	pid_t			pid;
	size_t			msg_num_bits;
	unsigned int	formula;
	size_t			bits_received;
	char			*msg;
	int				server_state;
	struct s_client	*next;
}					t_client;

typedef struct s_server
{
	pid_t		pid;
	pid_t		active_pid;
	t_client	*client;
	int			retry;
	int			online;
}				t_server;

t_client		*get_create_client(t_server *server, t_client **client,
					pid_t pid);
void			free_all(t_server *server);
void			get_active_pid(t_server *server);
unsigned int	ad_of_chars(char *str);
void			receive_hdr(int signal, t_server *server, t_client *client);
void			receive_formula(int signal, t_server *server, t_client *client);
void			init_msg_reception(t_client *client);
void			retry_server(t_server *server);

#endif
