/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo_dollar_j.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 00:12:44 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/09 14:00:16 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

/*This is when there is an echo $a msg that has to be without space at beggin*/
/*...or echo -n $a msg that also has to be without space 'msg' even is spaced*/
void	space_after_first_invalid_env(t_input *in, size_t w)
{
	if (!in->echo_error_n_arg && w == in->word_after_arg)
		in->spaced = 0;
	else if (w == in->word_after_command)
		in->spaced = 0;
}

/*Check if after the dollar there is a valid env variable with valid_env func*/
/*only spaces will be printed (if tocken was spaced) if echo msg1 $ msg2...*/
/*...so 1.no valid env (env_n < 0), 2. Not starting by alpha or '_', ...*/
/*... 3. only one $ sign, 4. is not quoted with "". echo msg1 $p msg2...*/
/*...won't be spaced -> msg1 msg2 not msg1  msg2. but echo msg1 "$p" msg2...*/
/*...will be double spaced -> msg1  msg2*/
void	print_if_spaced_and_valid_env(t_input *in, size_t w, int spaced)
{
	size_t	i;
	int		env_n;
	size_t	idollar;

	i = 0;
	in->dollars = 0;
	while (in->input_split[w][i] != '$')
		i++;
	idollar = i;
	while (in->input_split[w][i] == '$')
	{
		(in->dollars)++;
		i++;
	}
	env_n = valid_env((in->input_split[w] + i), in, w);
	if (env_n < 0
		&& (ft_isalpha(in->input_split[w][i]) || in->input_split[w][i] == '_')
		&& !idollar
		&& is_quoted(in, w) != 2 && in->dollars == 1)
		space_after_first_invalid_env(in, w);
	else if (spaced)
		printf(" ");
}

/*if we find a valid ENV variable it will print it if the number of $...*/
/*...previous to that VAR is ODD ($USER, $$$USER -> (pid)jrollon) if...*/
/*...it is EVEN ($$USER, $$$$USER -> (pid)USER). In Bash $$ prints the PID...*/
/*...here I just leave it blank.*/
/*IMPORTANT: you can see the printed is (n->dollars % 2) == 0 so EVEN, but...*/
/*...that is because the first $ is not counted. Only if there are several...*/
/*...will start to count. If only one $ n->dollars will be 0 (but one in... */
/*...reality as we are inside of this function if there is a $ found in str.*/
/*...Because we advance in 'i' several times we need to check if not \0 in...*/
/*...final line if (n->input_split[w][*i]) -> (*i)++;*/
int	print_valid_env_variable(t_input *n, size_t w, size_t *i)
{
	int		env_n;
	size_t	j;

	env_n = valid_env((n->input_split[w] + (*i) + 1), n, w);
	if (env_n > -1)
	{
		if (!(n->dollars % 2))
		{
			j = 0;
			while (n->envp[env_n][j] != '=')
				j++;
			printf("%s", (n->envp[env_n] + j + 1));
		}
		else
		{
			while (n->input_split[w][*i] && n->input_split[w][(*i) + 1] != ' ')
			{
				(*i)++;
				printf("%c", n->input_split[w][*i]);
			}
		}
	}
	if (n->input_split[w][*i])
		(*i)++;
	return (env_n);
}

void	print_invalid_envs(t_input *in, size_t w, size_t *i, int env_n)
{
	while (in->input_split[w][*i]
		&& in->input_split[w][(*i) + 1] != ' '
		&& in->input_split[w][*i] != '$')
	{
		if (in->dollars > 0 && (in->dollars % 2))
			printf("%c", in->input_split[w][*i]);
		(*i)++;
	}
	if (env_n < 0
		&& (ft_isalpha(in->input_split[w][in->idollar])
		|| in->input_split[w][in->idollar] == '_'))
		;
	else if (env_n < 0 && !(in->dollars % 2))
		printf("$");
}

void	manage_dollar(t_input *in, size_t w, int spaced)
{
	size_t	i;
	int		env_n;

	i = 0;
	print_if_spaced_and_valid_env(in, w, spaced);
	in->dollars = 0;
	while (in->input_split[w][i])
	{
		if (in->input_split[w][i] != '$')
			printf("%c", in->input_split[w][i]);
		else
		{
			while (in->input_split[w][i + 1] == '$')
			{
				i++;
				(in->dollars)++;
			}
			in->idollar = i + 1;
			env_n = print_valid_env_variable(in, w, &i);
			print_invalid_envs(in, w, &i, env_n);
		}
		if (in->input_split[w][i] && in->input_split[w][i] != '$')
			i++;
	}
}
