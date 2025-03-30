/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:54:07 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/30 20:12:07 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

/*usleep 1ms is necesary to not be so fast and jump over bits*/
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

void	send_char(char	c, pid_t pid)
{
	size_t			i;
	unsigned char	masc;

	i = 0;
	masc = 0x80;
	while (i < 8)
	{
		if (c & masc)
			kill(pid, B_1);
		else
			kill(pid, B_0);
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
	while (client->msg[i])
		send_char(client->msg[i++], client->server_pid);
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
