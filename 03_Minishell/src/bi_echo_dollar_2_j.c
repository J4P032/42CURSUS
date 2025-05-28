/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo_dollar_2_j.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:31:08 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/28 14:03:08 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

/*This is when there is an echo $a msg that has to be without space at beggin*/
/*...or echo -n $a msg that also has to be without space 'msg' even is spaced*/
/*Later are for cases as $a""a, echo $a"" a*, $a " " a or $a"$USER"*/
void	space_after_first_invalid_env(t_input *n, size_t w, size_t i, int on)
{
	if (!n->echo_error_n_arg && w == n->word_after_arg)
	{
		n->word_after_arg++;
		n->spaced = 0;
	}
	else if (w == n->word_after_command)
	{
		n->word_after_command++;
		n->spaced = 0;
	}
	if (on)
	{
		while (ft_isalnum(n->input_split[w][i]) && n->input_split[w][i])
			i++;
		if (n->input_split[w][i])
			ft_printf(" ");
		else if (n->input_split[w + 1] && n->input_split[w + 1][0] == ' '
			&& (n->status[w + 1] == SQUO_NSP || n->status[w + 1] == DQUO_NSP)
			&& (w > 0 && n->input_split[w - 1][0]))
			ft_printf(" ");
		else if (n->input_split[w + 1] && (w > 0 && n->input_split[w - 1][0])
			&& n->input_split[w + 2] && !n->input_split[w + 1][0]
			&& (n->status[w + 1] == SQUO_NSP || n->status[w + 1] == DQUO_NSP))
			ft_printf(" ");
	}
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
	if (env_n == -1
		&& (ft_isalpha(in->input_split[w][i]) || in->input_split[w][i] == '_')
		&& !idollar
		&& is_quoted(in, w) != 2 && in->dollars == 1)
		space_after_first_invalid_env(in, w, i, 1);
	else if (spaced)
		ft_printf(" ");
}

void	print_free_or_quoted_env(t_input *n, size_t j, size_t start, size_t w)
{
	while (n->envp[n->env_n][j] != '=')
		j++;
	j++;
	while (n->envp[n->env_n][j] == ' ' && is_quoted(n, w) == 0)
		j++;
	while (n->envp[n->env_n][j])
	{
		write(1, &n->envp[n->env_n][j++], 1);
		if (n->envp[n->env_n][j] == ' ' && is_quoted(n, w) == 0)
		{
			start = j;
			while (n->envp[n->env_n][j] == ' ')
			{
				if (n->envp[n->env_n][j] == '\0')
					break ;
				j++;
			}
			if (n->envp[n->env_n][j] != '\0')
				write(1, " ", 1);
			j = start;
		}
		while (n->envp[n->env_n][j] == ' ' && is_quoted(n, w) == 0)
			j++;
	}
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
void	print_valid_env_variable(t_input *n, size_t w, size_t *i)
{
	n->env_n = valid_env((n->input_split[w] + (*i) + 1), n, w);
	if (n->env_n > -1)
	{
		if (!(n->dollars % 2))
			print_free_or_quoted_env(n, 0, 0, w);
		else
		{
			while (n->input_split[w][*i] && n->input_split[w][(*i) + 1] != ' ')
				ft_printf("%c", n->input_split[w][++(*i)]);
		}
	}
	if (n->input_split[w][*i])
	{
		if (n->dollars % 2 == 0 && is_quoted(n, w) != 1 && n->env_n == -1
			&& (!n->input_split[w][n->idollar]
			|| n->input_split[w][n->idollar] == ' '))
			ft_printf("$");
		(*i)++;
	}
}
