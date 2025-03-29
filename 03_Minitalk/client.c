/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:54:07 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/29 20:48:49 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	send_num_bytes(t_client	*client)
{
	unsigned int	masc;
	size_t			i;

	i = 0;
	masc = 0x80000000;
	while (i < 32)
	{
		if (client->num_bytes & masc)
			kill(client->server_pid, B_1);
		else
			kill(client->server_pid, B_0);
		usleep(1);
		masc >>= 1;
		i++;
	}
}

void	process_msg(t_client *client)
{
	size_t	i;

	i = 0;
	client->num_bytes = ft_strlen(client->msg) * (sizeof(char));
	send_num_bytes(client);
/* 	while (client->msg[i])
	{
		process_char(client->msg[i]);
		i++;
	} */
}

int	main(int ac, char **av)
{
	t_client	*client;

	if (ac != 3)
		return (ft_printf("Error: Need: './client PID \"string\"'\n"), 1);
	client = (t_client *)ft_calloc(1, sizeof(t_client));
	if (!client)
		return (ft_printf("Error: Failure creating client"), 1);
	client->server_pid = ft_atoi(av[1]);
	client->client_pid = getpid();
	client->msg = av[2];
	if (kill(client->server_pid, 0) == -1)
		return (ft_printf("Error: Invalid PID\n"), free(client), 1);
	process_msg(client);
	free (client);
	return (0);

}
