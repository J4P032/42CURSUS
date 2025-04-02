/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:37:32 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/02 22:48:21 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client_bonus.h"

t_client	g_client;

/*Sends the number of chars that the server is going to expect*/
/*usleep 100ms is necesary to not be so fast and jump over bits*/
/*it compares num_bytes with a masc to know if we have a 0 or a 1 and it sends*/
/*store this signal sent to later compare with confirmation of server...*/
/*...and init the time to retries. Until it receives confirmation it stop...*/
/*...transmitting. When all bites sent client go to transmit msg state*/
void	send_num_bytes(void)
{
	int	server_status;

	if (g_client.bites_sent < 32)
	{
		if (g_client.num_bytes & g_client.masc_hdr)
		{
			server_status = kill(g_client.server_pid, B_1);
			g_client.last_bit_sent = B_1;
		}
		else
		{
			server_status = kill(g_client.server_pid, B_0);
			g_client.last_bit_sent = B_0;
		}
		if (server_status == -1)
			print_server_error();
		usleep(1);
		g_client.transmitting = 0;
		return ;
	}
	g_client.status = SENDING_FORMULA;
	g_client.bites_sent = 0;
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
		}
		else
		{
			server_status = kill(g_client.server_pid, B_0);
			g_client.last_bit_sent = B_0;
		}
		if (server_status == -1)
			print_server_error();
		usleep(1);
		g_client.transmitting = 0;
	}
}

/*This treats the confirmation from server. If the signal is same as transmit*/
/*it allows continue of next bit. If not it will send back again last bit sent*/
/*we have to count here the bites_sent because in function that sents not work*/
/*not a while because it will loop through every received signal from server*/
/*once we have reached 8 bits sent per char (1byte) it will reactivate masc*/
/*every char is sent through the index 0-7 first bits will be index 0 & so on*/
/*once all the bites sent then we go to MSG_SENT status*/
void	send_msg(int signal)
{
	if (signal == B_1)
	{
		g_client.bites_sent++;
		g_client.transmitting = 1;
		g_client.time = 0;
	}
	if (g_client.transmitting)
	{
		g_client.masc_msg >>= 1;
		if (g_client.bites_sent % 8 == 0)
			g_client.masc_msg = 0x80;
		send_char(g_client.msg[g_client.bites_sent / 8]);
	}
	if (g_client.bites_sent == g_client.num_bytes * 8)
		g_client.status = MSG_SENT;
}

/*This is the handler of the sigaction. It can only accept these parameters...*/
/*...no more, no less. So that is the reason to use a global variable, to send*/
/*...every variable there through the rest of functions.*/
/*SENDING_HDR will send the number of bytes to receive the server*/
/*It here confirm reception of server. SENDING_MSG will send the msg itself*/
/*usleep is necesary when last bite from SENDING_HDR 2 SENDING_MSG Noloosebits*/
void	process_msg(int signal, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (g_client.status == SENDING_HDR || g_client.status == SENDING_FORMULA)
		header_formula_send(signal, &g_client);
	usleep(1);
	if (g_client.status == SENDING_MSG)
		send_msg(signal);
	if (g_client.status == MSG_SENT && signal == B_1)
		exit (0);
	if (g_client.status == MSG_SENT && signal == B_0)
	{
		g_client.status = SENDING_MSG;
		g_client.masc_msg = 0x80;
		g_client.bites_sent = 0;
		send_char(g_client.msg[0]);
	}
}

/*send_num_byte needs to be here to kick the first bit sent. If not won't...*/
/*...continue as it depends on server confirmation. Sigaction will be the one*/
/*...to choose point what to do once the bit is received*/
int	main(int ac, char **av)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = process_msg;
	if (ac != 3)
		return (ft_printf("Error: Need: './client PID \"string\"'\n"), 1);
	g_client.server_pid = ft_atoi(av[1]);
	g_client.last_bit_sent = -1;
	g_client.bites_sent = 0;
	g_client.transmitting = 1;
	g_client.status = SENDING_HDR;
	g_client.msg = av[2];
	g_client.masc_hdr = 0x80000000;
	g_client.masc_formula = 0x80000000;
	g_client.masc_msg = 0x80;
	g_client.time = 0;
	g_client.num_bytes = ft_strlen(g_client.msg) * (sizeof(char));
	g_client.msg_formula = add_of_chars(g_client.msg);
	ft_printf("Formula: %u es", g_client.msg_formula);
	sigaction(B_0, &sa, NULL);
	sigaction(B_1, &sa, NULL);
	send_num_bytes();
	while (g_client.status != PRINT_CONFIRMED)
		wait_retry(&g_client);
	return (0);
}
