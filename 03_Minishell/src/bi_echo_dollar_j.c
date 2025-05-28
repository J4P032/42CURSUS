/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo_dollar_j.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 00:12:44 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/28 13:59:26 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

/*echo $$USER will print USER. $$USERp will be USERp.*/
/*j < in->env_len) is because $$2msg $$%msg to stop while print when not valid*/
/*break necesary to echo "$USER's not print the last R of USER. The i--..."*/
/*...to print the ' of same case*/
void	run_chars_after_the_dollar(t_input *in, size_t w, size_t *i, size_t j)
{
	while (in->input_split[w][*i] && in->input_split[w][(*i) + 1] != ' '
		&& in->input_split[w][*i] != '$' && in->env_n != -2)
	{
		if (is_quoted(in, w) == 2 && in->input_split[w][*i] == '\'')
		{
			if (*i > 0)
				(*i)--;
			break ;
		}
		if (in->dollars > 0 && (in->dollars % 2) && (j < in->env_len))
			ft_printf("%c", in->input_split[w][*i]);
		else if (j >= in->env_len
			&& !ft_isdigit(in->input_split[w][in->idollar])
			&& !ft_strrchr(D_Y_ODDCHAR, in->input_split[w][in->idollar])
			&& !ft_strrchr(N_ODDCHAR, in->input_split[w][in->idollar]))
		{
			in->spaced = 1;
			while (in->input_split[w][*i] && in->input_split[w][*i] != '?')
				ft_printf("%c", in->input_split[w][(*i)++]);
		}
		if (in->input_split[w][*i] && in->input_split[w][*i] != '?')
			(*i)++;
		(j)++;
	}
}

/*$ will be printed only if $ are ODD (1,3,5...). Here first $ is not...*/
/*...counted so to be ODD it has to be a EVEN number. That is the reason...*/
/*...of !(in->dollars % 2). BUT also can only be printed if after the $...*/
/*...(so idollar index) is not a possible valid ENV (starting with alpha...*/
/*...or a '_'. That is the reason I do nothing with it.*/
/*env_n = -2 is when there is an $? so print the exit code. It behaves as...*/
/*...BASH where echo $???msg will be number???msg*/
void	print_invalid_envs(t_input *in, size_t w, size_t *i)
{
	if (in->env_n > -1)
		in->env_len = validlen_env(in->envp[in->env_n], '=');
	else if (in->env_n == -1)
		in->env_len = invalidlen_env(in->input_split[w] + (*i));
	run_chars_after_the_dollar(in, w, i, 0);
	if (in->env_n < 0
		&& (ft_isalpha(in->input_split[w][in->idollar])
		|| in->input_split[w][in->idollar] == '_'))
		print_rest_no_env(in, w, i);
	else if (in->env_n == -1)
		print_rare_cases(in, w, i);
	else if (in->env_n == -2)
	{
		(*i)++;
		if (!(in->dollars % 2))
			ft_printf("%d", in->last_exit_code);
		else
			ft_printf("?");
		while (in->input_split[w][*i] && in->input_split[w][*i] != '$')
			ft_printf("%c", in->input_split[w][(*i)++]);
	}
}

/*for cases like echo "$ a". $ alone ones*/
void	check_previous_dollar(t_input *in, size_t w, size_t *i)
{
	if (*i > 0 && in->input_split[w][*i] == ' '
		&& in->input_split[w][(*i) - 1] == '$')
		ft_printf("%c", in->input_split[w][*i]);
	(*i)++;
}

/*idollar is the index of the next char after the last $ found*/
void	manage_dollar(t_input *in, size_t w, int spaced)
{
	size_t	i;

	i = 0;
	print_if_spaced_and_valid_env(in, w, spaced);
	in->dollars = 0;
	while (in->input_split[w][i])
	{
		if (in->input_split[w][i] != '$')
			ft_printf("%c", in->input_split[w][i]);
		else
		{
			while (in->input_split[w][i + 1] == '$')
			{
				i++;
				(in->dollars)++;
			}
			in->idollar = i + 1;
			print_valid_env_variable(in, w, &i);
			print_invalid_envs(in, w, &i);
		}
		if (in->input_split[w][i] && in->input_split[w][i] != '$')
			check_previous_dollar(in, w, &i);
	}
}
