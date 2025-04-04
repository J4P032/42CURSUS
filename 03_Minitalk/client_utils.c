/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:32:48 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/04 12:04:42 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	print_server_error(void)
{
	ft_printf("Error: Invalid PID or not have permissions\n");
	exit (1);
}

void	header_formula_send(int signal, t_client *client)
{
	if (signal == B_1)
	{
		client->bites_sent++;
		client->transmitting = 1;
		client->time = 0;
	}
	if (client->transmitting)
	{
		if (client->status == SENDING_HDR)
		{
			client->masc_hdr >>= 1;
			send_num_bytes();
			return ;
		}
		if (client->status == SENDING_FORMULA)
		{
			client->masc_formula >>= 1;
			send_formula(client);
			return ;
		}
	}
}

unsigned int	add_of_chars(char *str)
{
	unsigned int	solution;
	size_t			i;

	i = 0;
	solution = 0;
	while (str[i])
		solution += (unsigned int)str[i++];
	return (solution);
}

/*This Formula will add all the values of each char of the string...*/
/*...That way the server will compare with its received msg and see if is...*/
/*...the same. If not, The server will force the client to resend msg*/
/*...client->bites_sent = -1; because index of sending char will add...*/
/*...add it to cero in first iteration.*/
void	send_formula(t_client *client)
{
	int	server_status;

	if (client->bites_sent < 32)
	{
		if (client->msg_formula & client->masc_formula)
		{
			server_status = kill(client->server_pid, B_1);
			client->last_bit_sent = B_1;
		}
		else
		{
			server_status = kill(client->server_pid, B_0);
			client->last_bit_sent = B_0;
		}
		if (server_status < 0)
			print_server_error();
		usleep(100);
		client->transmitting = 0;
		return ;
	}
	client->status = SENDING_MSG;
	client->bites_sent = -1;
}

/*There are situations when 2 bits are together received by server and one...*/
/*...is lost. In that case I wait RETRY seconds and if not solved by it own...*/
/*...kick another bit sending the last one that should have been sent...*/
/*...of course we don't kick that bit if the msg already has been sent.*/
/*if (client->status == SENDING_FORMULA) send_formula(client); is...*/
/*...because between HDR and FORMULA it was sending this 'kick' kill again...*/
/*...the last one so it make a mistake. This way we override it.*/
void	wait_retry(t_client *client)
{
	int	server_status;

	server_status = 0;
	ft_printf("Server busy. Please Wait\r");
	if (client->status == SENDING_FORMULA)
		send_formula(client);
	if (client->time > RETRY && client->status < MSG_SENT)
	{
		server_status = kill(client->server_pid, client->last_bit_sent);
		if (server_status < 0)
			print_server_error();
		client->time = 0;
	}
	client->time++;
	usleep(250000);
}
