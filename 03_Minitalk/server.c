/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:37:30 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/30 20:14:51 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_server	*server;


void	write_client(t_client **client)
{
	t_client	*aux;

	aux = *client;
	while (aux)
	{
		if ((*client)->server_state == MSG_RECEIVED)
		{
			if (aux->msg)
			{
				ft_printf("%d: %s\n", aux->pid, aux->msg);
				free (aux->msg);
				aux->msg = NULL;
			}
			*client = aux->next;
			free (aux);
			aux = *client;
		}
		else
			aux = aux->next;
	}
}

void	init_msg_reception(t_client *client)
{
	client->server_state = RECEIVE_MSG;
	ft_printf("numBytes de %d es: %u bytes de mensaje\n", client->pid, client->msg_num_bits);
    client->bits_received = 0;
	client->msg = (char *)ft_calloc(client->msg_num_bits + 1, sizeof(char));
	client->msg_num_bits = 8 * client->msg_num_bits;
	if (!client->msg)
	{
		free_all(server);
		exit (1);
	}
}

/*detect the byte with %8 of the bites received*/
void	store_msg(int signal, t_client *client)
{
	size_t	index;

	index = client->bits_received / 8;
	if (client->bits_received % 8 == 0)
		client->msg[index] = 0;
	client->msg[index] <<= 1;
	if (signal == B_1)
		client->msg[index] |= 1;
	client->bits_received++;
}

void	process_header(int signal, siginfo_t *info, void *context)
{
	t_client	*client;
	size_t		i;

    (void)context;
	i = 0;
	client = get_create_client(server, &server->client, info->si_pid);
	client->pid = info->si_pid;
    if (client->server_state == RECEIVE_HDR && client->bits_received < 32)
    {
        client->msg_num_bits <<= 1;
        if (signal == B_1)
            client->msg_num_bits |= 1;
		client->bits_received++;
		if (client->bits_received == 32)
			init_msg_reception(client);
		return ;
    }
	if (client->server_state == RECEIVE_MSG
		&& client->bits_received < client->msg_num_bits)
			store_msg(signal, client);
	if (client->bits_received == client->msg_num_bits)
		client->server_state = MSG_RECEIVED;
	write_client (&server->client);
}

/*pid_t is an alias (typedef) defined in sys/types.hSA_SIGINFOto use pid_t instead int*/
/*sigaction struct will process each signal received. flag SA_SIGINFO will...*/
/*...FORCE to to use sa_sigaction function to extract extra info from client*/
/*...if not used SA_SIGINFO it will use sa_handler function*/
/*To allow visual studio IntelliSense I had to add a lua c_cpp_properties.json*/
/*pause() halt the program until a new signal is recieved so no CPU load*/
int	main(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = process_header;
	server = (t_server *)ft_calloc(1, sizeof(t_server));
	if (!server)
		return (ft_printf("Error: Failure creating server", 1));
	server->pid = getpid();
	server->online = 1;
	ft_printf("Server PID: %d\n", server->pid);
	sigaction(B_0, &sa, NULL);
	sigaction(B_1, &sa, NULL);
	while (server->online)
		pause();
	free (server);
	return (0);
}
