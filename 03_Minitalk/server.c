/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:37:30 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/29 20:59:36 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include <stdio.h>//

t_server	*server;

void process_header(int signal, siginfo_t *info, void *context)
{
    static size_t	num_bytes = 0;
	static int 		bit_count = 0;

    (void)context;
    if (bit_count < 32)
    {
        num_bytes <<= 1;
        if (signal == B_1)
            num_bytes |= 1;
		bit_count++;
		if (bit_count == 32)
        {
			server->client.pid = info->si_pid;
			server->client.num_bits = 8 * num_bytes;
			ft_printf("numBytes de %d es: %u bytes de mensaje\n", server->client.pid, num_bytes);
            bit_count = 0;
        }
    }
}

/*pid_t is an alias (typedef) defined in sys/types.h that usually returns an..*/
/*...int but it can be a long so that is the reason to use pid_t instead int*/
/*sigaction struct will process each signal received. flag SA_SIGINFO will...*/
/*...FORCE to to use sa_sigaction function to extract extra info from client*/
/*...if not used SA_SIGINFO it will use sa_handler function*/
int	main(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = process_header;
	server = (t_server *)ft_calloc(1, sizeof(t_server));
	if (!server)
		return (ft_printf("Error: Failure creating server", 1));
	server->pid = getpid();
	server->online = 1;
	ft_printf("Server PID: %d\n", server->pid);
	sigaction(B_0, &sa, NULL);
	sigaction(B_1, &sa, NULL);
	while (server->online)
		pause();
	free (server);
	return (0);
}
