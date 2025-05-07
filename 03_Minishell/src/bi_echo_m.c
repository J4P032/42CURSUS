/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo_m.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:50:16 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/07 22:06:37 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

size_t	check_rest_of_n(t_input *in)
{
	size_t	i;
	size_t	j;
	size_t	n_repeated;

	n_repeated = 1;
	j = in->word_after_arg;
	while (j < in->input_words)
	{
		i = 1;
		compose_arg(in, j);
		while (in->args[i] && n_repeated)
		{
			if (in->args[0] != '-' || in->args[i++] != 'n')
				n_repeated = 0;
		}
		if (ft_strncmp(in->args, "-n", 2) != 0)
			n_repeated = 0;
		if (n_repeated == 0)
			break ;
		j++;
	}
	return (j);
}

size_t	give_me_the_fist_word(t_input *in, int *error_argument)
{
	size_t	i;
	size_t	n_repeated;

	i = 1;
	n_repeated = 1;
	while (in->args[i])
	{
		if (in->args[i++] != 'n' || in->args[0] != '-')
		{
			n_repeated = 0;
			*error_argument = 1;
		}
	}
	if (ft_strncmp(in->args, "-n", 2) != 0)
		*error_argument = 1;
	if (*error_argument == 0 && n_repeated)
		i = check_rest_of_n(in);
	else
		i = in->word_after_command;
	return (i);
}

void	manage_dollar(t_input *in, size_t w, int spaced)
{
	size_t	i;
	size_t	j;
	size_t	dollars;
	int		env_n;

	i = 0;
	dollars = 0;
	if (spaced)
		printf(" ");
	while (in->input_split[w][i])
	{
		if (in->input_split[w][i] != '$')
			printf("%c", in->input_split[w][i]);
		else
		{
			while (in->input_split[w][i + 1] == '$')
			{
				i++;
				dollars++;
			}
			env_n = valid_env((in->input_split[w] + i + 1), in, w);
			if (env_n > -1)
			{
				if (!(dollars % 2))
				{
					j = 0;
					while (in->envp[env_n][j] != '=')
						j++;
					printf("%s", (in->envp[env_n] + j + 1));
				}
				else
				{
					while (in->input_split[w][i] && in->input_split[w][i + 1] != ' ')
					{
						i++;
						printf("%c", in->input_split[w][i]);
					}
				}
			}
			while (in->input_split[w][i] && in->input_split[w][i + 1] != ' ')
				i++;
			if (!(dollars % 2))
				printf("$");
		}
		if (in->input_split[w][i])
			i++;
	}		
} 

void	print_arguments(t_input *in, size_t	w, int spaced)
{
	size_t	i;
	int		print_as_env;

	i = 0;	
	print_as_env = (is_quoted(in, w) == 2 || !is_quoted(in, w));
	if (spaced)
	{
		if (ft_strrchr(in->input_split[w], '$') && print_as_env)
			manage_dollar(in, w, 1);
		else
			printf(" %s", in->input_split[w]);
	}
	else
	{
		if (ft_strrchr(in->input_split[w], '$') && print_as_env)
			manage_dollar(in, w, 0);
		else		
			printf("%s", in->input_split[w]);
	}
}

/*start is because the first argument from the command or the -n even it is...*/
/*...spaced it dont have to space it when printed.*/
void	ft_echo(t_input *in)
{
	size_t	i;
	size_t	start;
	int		error_argument;

	error_argument = 0;
	start = give_me_the_fist_word(in, &error_argument);
	i = start;
	while (i < in->input_words && in->input_split && in->input_split[i])
	{
		if ((in->status[i] == EPTY_SP || in->status[i] == SQUO_SP
				|| in->status[i] == DQUO_SP) && in->input_split[i][0]
				&& i != start)
			print_arguments(in, i, 1);
		else if ((in->status[i] == EPTY_SP || in->status[i] == SQUO_SP
				|| in->status[i] == DQUO_SP) && in->input_split[i][0] == '\0'
				&& i != start)
			printf(" ");
		else if (in->input_split[i][0])
			print_arguments(in, i, 0);
		i++;
	}
	if (error_argument == 1)
		printf("\n");
}
