/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:38:35 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/04 12:41:27 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server_bonus.h"

unsigned int	ad_of_chars(char *str)
{
	unsigned int	solution;
	size_t			i;

	i = 0;
	solution = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		solution += (unsigned int)str[i];
		i++;
	}
	return (solution);
}

void	receive_hdr(int signal, t_server *server, t_client *client)
{
	if (server->active_pid == client->pid)
	{
		client->msg_num_bits <<= 1;
		if (signal == B_1)
			client->msg_num_bits |= 1;
		kill(client->pid, B_1);
		client->bits_received++;
	}
	if (client->bits_received == 32)
		init_msg_reception(client);
}

void	receive_formula(int signal, t_server *server, t_client *client)
{
	if (server->active_pid == client->pid)
	{
		client->formula <<= 1;
		if (signal == B_1)
			client->formula |= 1;
		kill(client->pid, B_1);
		client->bits_received++;
	}
	if (client->bits_received == 32)
	{
		client->bits_received = 0;
		client->server_state = RECEIVE_MSG;
	}
}

/*This function is in case the client crash while sending a msg.*/
/*Because the server makes exclusive a client with active_pid if client...*/
/*...crashes, that client will never change to MSG_PRINTED so server will...*/
/*...wait for ever for a signal from a crashed client. This way once 5 seconds*/
/*...it will send a 'ping' to the active_pid client. If it is < 0 means it...*/
/*...doesn't exist, so it will force that client to MSG_PRINTED so active_pid*/
/*...will change to next client (if exists). IT IS VERY IMPORTANT, that...*/
/*...in the handler sigaction function we reset the server->retry back to cero*/
/*...with each byte received from the client, because if not, it will send...*/
/*...this ping B_1 signal to client modifying the msg each time. AS it only...*/
/*...send it the ping to the active_pid, it won't reactivate the waiting...*/
/*...clients. OFUUUUUUU!!! someone said this Minitalk is easy!!???*/
void	retry_server(t_server *server)
{
	int			client_status;
	t_client	*aux;

	client_status = 0;
	aux = server->client;
	if (server->retry > 40)
	{
		client_status = kill(server->active_pid, B_1);
		if (client_status < 0)
		{
			while (aux && aux->pid != server->active_pid)
				aux = aux->next;
			if (aux)
				aux->server_state = MSG_PRINTED;
		}
		server->retry = 0;
	}
	usleep(125000);
	server->retry++;
}
