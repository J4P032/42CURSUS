/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:11:08 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/04 11:45:13 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

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
