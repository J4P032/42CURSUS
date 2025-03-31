/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 11:32:04 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/31 20:24:28 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	CLIENT_H
# define CLIENT_H
# include <signal.h>
# include <sys/types.h>
# include "./ft_printf/ft_printf.h"
# include "./libft/libft.h"

# define B_0 SIGUSR1
# define B_1 SIGUSR2

typedef struct	s_client
{
	pid_t	client_pid;
	pid_t	server_pid;
	size_t	num_bytes;
	int		last_bit_sent;
	char	*msg;
}			t_client;

extern t_client	client;

#endif
