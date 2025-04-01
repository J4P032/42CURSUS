/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 13:46:21 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/31 18:08:18 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	free_all(t_server *server)
{
	t_client	*aux;
	t_client	*aux2;

	aux = NULL;
	if (server)
	{
		aux = server->client;
		while (aux)
		{
			aux2 = aux;
			if (aux->msg)
			{
				free (aux->msg);
				aux->msg = NULL;
			}
			aux = aux->next;
			free(aux2);
		}
		free (server);
		server = NULL;
	}
}

t_client	*create_new_client(t_server *server)
{
	t_client	*client;
	t_client	*aux;

	aux = server->client;
	client = (t_client *)ft_calloc(1, sizeof(t_client));
	if (!client)
	{
		ft_printf("Error: failure creating client");
		free_all(server);
		exit (1);
	}
	while (aux && aux->next)
		aux = aux->next;
	if (!aux)
	{
		server->client = client;
		return (client);
	}
	aux->next = client;
	return (client);
}

t_client	*search_client(t_client *client, pid_t pid)
{
	while (client)
	{
		if (client->pid == pid)
			return (client);
		else
			client = client->next;
	}
	return (client);
}

t_client	*get_create_client(t_server *server, t_client **client, pid_t pid)
{
	t_client	*aux;

	if (!(*client))
	{
		*client = create_new_client(server);
		(*client)->pid = pid;
		return (*client);
	}
	aux = search_client(*client, pid);
	if (!aux)
	{
		aux = create_new_client(server);
		aux->pid = pid;
	}
	return (aux);
}
