/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:54:07 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/04 12:14:30 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

t_client	g_client;

/*Sends the number of chars that the server is going to expect*/
/*usleep 1ms is necesary to not be so fast and jump over bits*/
/*it compares num_bytes with a masc to know if we have a 0 or a 1 and it sends*/
/*store this signal sent in case we need to 'kick' the kill again with a...*/
/*...server busy state. Until it receives confirmation it stop...*/
/*...transmitting. When all bites sent client go to sending FORMULA to compare*/
void	send_num_bytes(void)
{
	int	server_status;

	if (g_client.num_bytes == 0)
		exit (0);
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
		if (server_status < 0)
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
		if (server_status < 0)
			print_server_error();
		usleep(1);
		g_client.transmitting = 0;
	}
}

/*This treats the confirmation from server. It allows continue of next bit.*/
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
/*SENDING_FORMULA is a confirmation that the msg is the same in server 2 print*/
/*It here confirm reception of server. SENDING_MSG will send the msg itself*/
/*usleep is necesary when last bite from SENDING_HDR 2 SENDING_MSG Noloosebits*/
/*When the MSG_(is)SENT* the SERVER will send a B_1 if the msg is the same...*/
/*...as the one sent from the client. If not, SERVER will send a B_0 to...*/
/*...order the client to send back the full msg.*/
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
/*wait retry is a function to allow resend of last sent bit in case of...*/
/*...server busy*/
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
	sigaction(B_0, &sa, NULL);
	sigaction(B_1, &sa, NULL);
	send_num_bytes();
	while (g_client.status != PRINT_CONFIRMED)
		wait_retry(&g_client);
	return (0);
}
