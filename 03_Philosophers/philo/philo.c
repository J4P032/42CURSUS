/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:38:23 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/17 21:25:56 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*give_me_last(t_game *game)
{
	t_philo	*aux;

	aux = game->philo;
	while (aux->next)
		aux = aux->next;
	return (aux);
}

/*gettimeofday saves time now in sec and microsec in struct start_game_time...*/
/*...timeval struct is .tv_sec (*1000 to milisecs) and .tv_usec...*/
/*...(/1000 to milisecs)*/
/*I create a circular list*/
int	init_philo(t_game *game)
{
	size_t	i;
	t_philo	*aux;
	t_philo	*last;

	i = 1;
	game->philo = (t_philo *)ft_calloc(1, sizeof(t_philo));
	aux = game->philo;
	if (!game->philo)
		return (free_all(game), 0);
	game->philo->id = 1;
	while ((long)i < game->num_philos)
	{
		aux = (t_philo *)ft_calloc(1, sizeof(t_philo));
		if (!aux)
			return (free_all(game), 0);
		aux->id = i + 1;
		last = give_me_last(game);
		last->next = aux;
		aux->prev = last;
		i++;
	}
	aux->next = game->philo;
	game->philo->prev = aux;
	game->one_died = 0;
	return (1);
}

void	init_game_rules(t_game *game, int argc, char **argv, int *error)
{
	game->num_philos = ft_atol(argv[1], error);
	game->time_2_die = ft_atol(argv[2], error);
	game->time_2_eat = ft_atol(argv[3], error);
	game->time_2_sleep = ft_atol(argv[4], error);
	if (*error)
		printf("Error: Arguments must be in LONG numbers range.\n");
	if (argc == 6)
	{
		game->num_times_2_eat = ft_atol(argv[5], error);
		if (game->num_times_2_eat < 0)
		{
			*error = 1;
			printf("Error: Only positive arguments allowed\n");
			return ;
		}
	}
	else
		game->num_times_2_eat = -1;
	if (game->time_2_die < 0 || game->time_2_eat < 0 || game->time_2_sleep < 0)
	{
		*error = 1;
		printf("Error: Only positive arguments allowed\n");
	}
	game->running = 0;
	game->philos_eatten = 0;
}

void	wait_for_threads_to_end(t_game *game)
{
	t_philo	*aux;

	aux = game->philo;
	pthread_join(aux->thread, NULL);
	aux = aux->next;
	while (aux->id != 1)
	{
		pthread_join(aux->thread, NULL);
		aux = aux->next;
	}
	pthread_join(game->judge, NULL);
}

/*Test to see all have eatten minimun times:
t_philo *aux = game.philo;
if (argc == 6 && game.num_philos != 1)
{
	printf("\nPhilos Eatten: %ld\n", game.philos_eatten);
	printf("%d\tEated: %ld\n", aux->id, aux->times_eatten);
	aux = aux->next;
	while (aux->id != 1)
	{
		printf("%d\tEated: %ld\n", aux->id, aux->times_eatten);
		aux = aux->next;
	}
}
*/
int	main(int argc, char **argv)
{
	t_game		game;
	int			error;

	error = 0;
	if (arg_errors(argc, &game, error, 1))
		return (1);
	init_game_rules(&game, argc, argv, &error);
	if (game.num_philos < 1 || game.num_philos > PHILOS_MAX || error)
		return (arg_errors(argc, &game, error, 0), 1);
	if (!init_philo(&game))
		return (printf("Error: Memory problems\n"), 1);
	if (!create_threads(&game))
		return (free_all(&game), 1);
	wait_for_threads_to_end(&game);
	mutex_destroyer(&game);
	free_all(&game);
	return (0);
}
