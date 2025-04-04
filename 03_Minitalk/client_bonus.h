/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:37:46 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/04 12:38:07 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_BONUS_H
# define CLIENT_BONUS_H
# include <signal.h>
# include <sys/types.h>
# include "./ft_printf/ft_printf.h"
# include "./libft/libft.h"

# define B_0 SIGUSR1
# define B_1 SIGUSR2
# define SENDING_HDR 0
# define SENDING_FORMULA 1
# define SENDING_MSG 2
# define MSG_SENT 3
# define PRINT_CONFIRMED 4
# define RETRY 4

typedef struct s_client
{
	pid_t			server_pid;
	int				num_bytes;
	int				bites_sent;
	int				last_bit_sent;
	char			*msg;
	int				transmitting;
	int				status;
	size_t			time;
	unsigned int	masc_hdr;
	unsigned int	masc_formula;
	unsigned char	masc_msg;
	unsigned int	msg_formula;
}			t_client;

void			print_server_error(void);
void			wait_retry(t_client *client);
unsigned int	add_of_chars(char *str);
void			send_formula(t_client *client);
void			send_num_bytes(void);
void			header_formula_send(int signal, t_client *client);

#endif
