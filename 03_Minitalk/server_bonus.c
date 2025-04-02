/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:38:08 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/02 22:49:14 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server_bonus.h"

t_server	*g_server;

/*11 in strncmp because if stopservera for example it was 10 that way it will*/
/*... count the \0 and not in the middle of a string*/
/*If it finds MSG_RECEIVED it will print it and will turn it to PRINTED to...*/
/*...not write it again.*/
void	write_client(void)
{
	t_client	*aux;
	const char	stopserver[] = "StopServer";

	aux = g_server->client;
	while (aux)
	{
		if (aux->server_state == MSG_RECEIVED)
		{
			if (aux->msg && ad_of_chars(aux->msg) == aux->formula)
			{
				ft_printf("%d: %s\n", aux->pid, aux->msg);
				if (!ft_strncmp(aux->msg, stopserver, 11))
					g_server->online = 0;
				kill(aux->pid, B_1);
				aux->server_state = MSG_PRINTED;
			}
			else
			{
				usleep(100);
				kill(aux->pid, B_0);
				aux->server_state = RECEIVE_MSG;
			}
		}
		aux = aux->next;
	}
}

/*init back the bits_received as a counter later to compare with msg bits*/
/*first msg_num_bits is BYTES of MSG to compose malloc. Later turn to bits*/
void	init_msg_reception(t_client *client)
{
	client->server_state = RECEIVE_FORMULA;
	client->bits_received = 0;
	client->msg = (char *)ft_calloc(client->msg_num_bits + 1, sizeof(char));
	if (!client->msg)
	{
		free_all(g_server);
		exit (1);
	}
	client->msg_num_bits = 8 * client->msg_num_bits;
}

/*detect the byte with %8 of the bites received*/
/*we send back the signal received to the client to continue with its sending*/
void	store_msg(int signal, t_client *client)
{
	size_t	index;

	if (g_server->active_pid == client->pid)
	{
		index = client->bits_received / 8;
		if (client->msg)
			client->msg[index] <<= 1;
		if (signal == B_1)
			client->msg[index] |= 1;
		kill(client->pid, B_1);
		client->bits_received++;
	}
}

/*The reason to use a global variable is because we cannot modify the...*/
/*...params of this funcion as it is ruled by sigaction. So we need to...*/
/*...access the variables in other parts of the program*/
/*get_create_client will search for an already created client in the list*/
/*if not found by the PID, then will create a new node and join to the rest*/
/*once we have it we re-compose the INT received as HDR and then pass to...*/
/*...the receive msg state, where we will point to store the msg into a str*/
/*in every moment we see if there is something to write (once the str is...)*/
/*...completed*/
/*NEW! I added an active pid to only process one client at a time*/
void	process_header_msg(int signal, siginfo_t *info, void *context)
{
	t_client	*client;

	(void)context;
	client = get_create_client(g_server, &g_server->client, info->si_pid);
	get_active_pid(g_server);
	if (client->server_state == RECEIVE_HDR && client->bits_received < 32)
	{
		receive_hdr(signal, g_server, client);
		return ;
	}
	if (client->server_state == RECEIVE_FORMULA && client->bits_received < 32)
	{
		receive_formula(signal, g_server, client);
		return ;
	}
	if (client->server_state == RECEIVE_MSG
		&& client->bits_received < client->msg_num_bits && client->msg)
		store_msg(signal, client);
	if (client->bits_received == client->msg_num_bits)
		client->server_state = MSG_RECEIVED;
	write_client ();
}

/*pid_t is an alias (typedef) defined in sys/types.h instead int.*/
/*sigaction struct will process each signal received. flag SA_SIGINFO will...*/
/*...FORCE to to use sa_sigaction function to extract extra info from client*/
/*...if not used SA_SIGINFO it will use sa_handler function*/
/*To allow visual studio IntelliSense I had to add a lua c_cpp_properties.json*/
/*pause() halt the program until a new signal is recieved so no CPU load*/
/*even is a infinite while, it only admit signals. Won't malloc server again*/
int	main(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = process_header_msg;
	g_server = (t_server *)ft_calloc(1, sizeof(t_server));
	if (!g_server)
		return (ft_printf("Error: Failure creating server", 1));
	g_server->pid = getpid();
	g_server->online = 1;
	ft_printf("Server PID: %d\n", g_server->pid);
	sigaction(B_0, &sa, NULL);
	sigaction(B_1, &sa, NULL);
	while (g_server->online)
		pause();
	free_all(g_server);
	return (0);
}
