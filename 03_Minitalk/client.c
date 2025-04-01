/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:54:07 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/01 19:50:38 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

t_client	g_client;

/*usleep 100ms is necesary to not be so fast and jump over bits*/
void	send_num_bytes(void)
{
	int	server_status;

	if (g_client.bites_sent < 32)
	{
		if (g_client.num_bytes & g_client.masc_hdr)
		{
			server_status = kill(g_client.server_pid, B_1);
			g_client.last_bit_sent = B_1;
			g_client.time = 1;
		}
		else
		{
			server_status = kill(g_client.server_pid, B_0);
			g_client.last_bit_sent = B_0;
			g_client.time = 1;
		}
		if (server_status == -1)
			print_server_error();
		usleep(100);
		g_client.transmitting = 0;
		return ;
	}
	g_client.status = SENDING_MSG;
	g_client.bites_sent = -1;
}

void	send_char(char c)
{
	int	server_status;

	if (g_client.bites_sent < g_client.num_bytes * 8)
	{
		if (c & g_client.masc_msg)
		{
			server_status = kill(g_client.server_pid, B_1);
			g_client.last_bit_sent = B_1;
			g_client.time = 1;
		}
		else
		{
			server_status = kill(g_client.server_pid, B_0);
			g_client.last_bit_sent = B_0;
			g_client.time = 1;
		}
		if (server_status == -1)
			print_server_error();
		usleep(100);
		g_client.transmitting = 0;
	}
}

void	send_msg(int signal)
{
	if (signal == g_client.last_bit_sent)
		g_client.transmitting = 1;
	else
		kill(g_client.server_pid, g_client.last_bit_sent);
	if (g_client.transmitting)
	{
		g_client.bites_sent++;
		g_client.masc_msg >>= 1;
		if (g_client.bites_sent % 8 == 0)
			g_client.masc_msg = 0x80;
		send_char(g_client.msg[g_client.bites_sent / 8]);
	}
	if (g_client.bites_sent == g_client.num_bytes * 8)
		g_client.status = MSG_SENT;
}

void	process_msg(int signal, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (g_client.status == SENDING_HDR)
	{
		if (signal == g_client.last_bit_sent)
		{
			g_client.transmitting = 1;
			g_client.time = 0;
		}
		else
			kill(g_client.server_pid, g_client.last_bit_sent);
		if (g_client.transmitting)
		{
			g_client.bites_sent++;
			g_client.masc_hdr >>= 1;
			send_num_bytes();
		}
	}
	usleep(100);
	if (g_client.status == SENDING_MSG)
		send_msg(signal);
}

int	main(int ac, char **av)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = process_msg;
	if (ac != 3)
		return (ft_printf("Error: Need: './client PID \"string\"'\n"), 1);
	g_client.server_pid = ft_atoi(av[1]);
	g_client.client_pid = getpid(); // para que?
	g_client.last_bit_sent = -1;
	g_client.bites_sent = 0;
	g_client.transmitting = 1;
	g_client.status = SENDING_HDR;
	g_client.msg = av[2];
	g_client.masc_hdr = 0x80000000;
	g_client.masc_msg = 0x80;
	g_client.time = 0;
	g_client.num_bytes = ft_strlen(g_client.msg) * (sizeof(char)); //checkear que no hace falta sizeof
	sigaction(B_0, &sa, NULL);
	sigaction(B_1, &sa, NULL);
	send_num_bytes();
	while (g_client.status != MSG_SENT)
		wait_retry(&g_client);
	return (0);
}
