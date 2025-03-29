/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 14:28:42 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/29 19:48:38 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	SERVER_H
# define SERVER_H
//# define _POSIX_C_SOURCE 199309L
# include <signal.h>
# include <sys/types.h>
# include "./ft_printf/ft_printf.h"
# include "./libft/libft.h"

# define B_0 SIGUSR1
# define B_1 SIGUSR2

typedef struct s_client
{
	pid_t	pid;
	size_t	num_bits;
	char	*msg;
}			t_client;

typedef struct	s_server
{
	pid_t		pid;
	t_client	client;
	int			online;
}				t_server;

extern t_server	*server;

#endif
