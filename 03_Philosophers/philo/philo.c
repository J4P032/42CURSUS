/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:38:23 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/09 18:01:46 by jrollon-         ###   ########.fr       */
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
	t_philo *last;

	i = 1;
	gettimeofday(&game->start_game_time, NULL); 
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
	return (1);
}

void	init_game_rules(t_game *game, int argc, char **argv, int *error)
{
	game->num_philos = ft_atol(argv[1], error);
	game->time_2_die = ft_atol(argv[2], error);
	game->time_2_eat = ft_atol(argv[3], error);
	game->time_2_sleep = ft_atol(argv[4], error);
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
	if (game->num_philos <= 0 || game->time_2_die < 0 || game->time_2_eat < 0 ||
		game->time_2_sleep < 0)
	{	
		*error = 1;
		printf("Error: Only positive arguments allowed and philos > 0\n");
	}	
	if (game->num_philos > PHILOS_MAX)
		*error = 1;
	game->running = 1;
}

int	main(int argc, char **argv)
{
	t_game	game;
	int		error;
	t_philo *aux;//

	error = 0;
	if (argc < 5 || argc > 6)
	{
		printf("please: ./philo num_philos time_2die time_2eat time_2sleep\n");
		printf("you can add another arg at the end of num_times_philo_eat\n");
		return (1);
	}
	init_game_rules(&game, argc, argv, &error);
	if (error)
	{
		printf("Error: num_philos > %d. Args must be LONG range", PHILOS_MAX);
		return (1);
	}
	if (!init_philo(&game))
		return (1);
	while (game.running)
	{
		aux = game.philo;
		printf("%d\n", aux->id);
		aux = aux->prev;
		while (aux->id != 1)
		{
			printf("%d\n", aux->id);
			aux = aux->prev;
		}
		game.running = 0;
	}
	free_all(&game);
	return (0);
}
