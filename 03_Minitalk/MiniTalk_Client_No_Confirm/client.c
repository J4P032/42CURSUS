/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:54:07 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/31 20:25:38 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

t_client	client;

/*usleep 100ms is necesary to not be so fast and jump over bits*/
void	send_num_bytes(void)
{
	unsigned int	masc;
	int				server_status;
	size_t			i;

	i = 0;
	masc = 0x80000000;
	while (i < 32)
	{
		if (client.num_bytes & masc)
			server_status = kill(client.server_pid, B_1);
		else
			server_status = kill(client.server_pid, B_0);
		if (server_status == -1)
		{
			ft_printf("Error: Invalid PID\n");
			exit (1);
		}
		usleep(100);
		masc >>= 1;
		i++;
	}
}

void	send_char(char	c)
{
	size_t			i;
	int				server_status;
	unsigned char	masc;

	i = 0;
	masc = 0x80;
	while (i < 8)
	{
		if (c & masc)
			server_status = kill(client.server_pid, B_1);
		else
			server_status = kill(client.server_pid, B_0);
		if (server_status == -1)
		{
			ft_printf("Error: Invalid PID\n");
			exit (1);
		}
		usleep(100);
		masc >>= 1;
		i++;
	}
}

void	process_msg(void)
{
	size_t	i;

	i = 0;
	client.num_bytes = ft_strlen(client.msg) * (sizeof(char));
	send_num_bytes();
	usleep(100);
	while (client.msg[i])
		send_char(client.msg[i++]);
}

void	confirmation(int signal, siginfo_t *info, void *context)
{
	(void)context;
	(void)signal;
	(void)info;
}


int	main(int ac, char **av)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = confirmation; //
	if (ac != 3)
		return (ft_printf("Error: Need: './client PID \"string\"'\n"), 1);
	client.server_pid = ft_atoi(av[1]);
	client.client_pid = getpid();
	client.last_bit_sent = -1;
	client.msg = av[2];
	sigaction(B_0, &sa, NULL);
	sigaction(B_1, &sa, NULL);
	process_msg();
	return (0);
}
