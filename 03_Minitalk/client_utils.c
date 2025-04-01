/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:32:48 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/01 20:39:53 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	print_server_error(void)
{
	ft_printf("Error: Invalid PID or not have permissions\n");
	exit (1);
}
void	wait_retry(t_client *client)
{
	ft_printf("\ntime:%u", client->time);//
	ft_printf("\nprocess:%d\n", client->status);//
	if (!client->transmitting && client->time > RETRY)
		kill(client->server_pid, client->last_bit_sent);// cuando pase ponerlo a cero el time.
	client->time++;
	sleep(1);
}
