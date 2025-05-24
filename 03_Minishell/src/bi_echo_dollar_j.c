/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo_dollar_j.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 00:12:44 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/24 23:00:22 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

/*This is when there is an echo $a msg that has to be without space at beggin*/
/*...or echo -n $a msg that also has to be without space 'msg' even is spaced*/
/*Later are for cases as $a""a, echo $a"" a*, $a " " a or $a"$USER"*/
void	space_after_first_invalid_env(t_input *in, size_t w, size_t i, int on)
{
	if (!in->echo_error_n_arg && w == in->word_after_arg)
	{
		in->word_after_arg++;
		in->spaced = 0;
	}
	else if (w == in->word_after_command)
	{
		in->word_after_command++;
		in->spaced = 0;
	}
	if (on)
	{
		while (ft_isalnum(in->input_split[w][i]) && in->input_split[w][i])
			i++;
		if (in->input_split[w][i])
			ft_printf(" ");
		else if (in->input_split[w + 1] && in->input_split[w + 1][0] == ' ' && 
			(in->status[w + 1] == SQUO_NSP || in->status[w + 1] == DQUO_NSP))
			ft_printf(" ");
		else if (in->input_split[w + 1]
			&& in->input_split[w + 2] && !in->input_split[w + 1][0]
			&&	(in->status[w + 1] == SQUO_NSP || in->status[w + 1] == DQUO_NSP))
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
				write(1, " ", 1);;
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
	size_t	j;
	size_t	start;

	n->env_n = valid_env((n->input_split[w] + (*i) + 1), n, w);
	if (n->env_n > -1)
	{
		if (!(n->dollars % 2))
		{
			j = 0;
			start = 0;
			print_free_or_quoted_env(n, j, start, w);
		}
		else
		{
			while (n->input_split[w][*i] && n->input_split[w][(*i) + 1] != ' ')
				ft_printf("%c", n->input_split[w][++(*i)]);
		}
	}
	if (n->input_split[w][*i])
	{
		if(n->dollars % 2 == 0 && is_quoted(n, w) != 1 && n->env_n == -1
			&& (!n->input_split[w][n->idollar] || n->input_split[w][n->idollar] == ' '))
			ft_printf("$");
		(*i)++;
	}
}

/*echo $$USER will print USER. $$USERp will be USERp. That is the first while*/
/*$ will be printed only if $ are ODD (1,3,5...). Here first $ is not...*/
/*...counted so to be ODD it has to be a EVEN number. That is the reason...*/
/*...of !(in->dollars % 2). BUT also can only be printed if after the $...*/
/*...(so idollar index) is not a possible valid ENV (starting with alpha...*/
/*...or a '_'. That is the reason I do nothing with it.*/
/*env_n = -2 is when there is an $? so print the exit code. It behaves as...*/
/*...BASH where echo $???msg will be number???msg*/
void	print_invalid_envs(t_input *in, size_t w, size_t *i, int env_n)
{
	//size_t	env_len;
	size_t	j;

	j = 0;
	if (env_n > -1)
		in->env_len = validlen_env(in->envp[env_n], '=');
	else if (env_n == -1)
		in->env_len = invalidlen_env(in->input_split[w] + (*i));
	while (in->input_split[w][*i]
		&& in->input_split[w][(*i) + 1] != ' '
		&& in->input_split[w][*i] != '$'
		&& env_n != -2)//cuidado ese -2 nuevo que es $?
	{
		if (is_quoted(in, w) == 2 && in->input_split[w][*i] == '\'')
		{
			if (*i > 0)
				(*i)--;
			break ;
		}
		if (in->dollars > 0 && (in->dollars % 2) && (j < in->env_len))
			ft_printf("%c", in->input_split[w][*i]);
		else if (j >= in->env_len && !ft_isdigit(in->input_split[w][in->idollar])
			&& !ft_strrchr(D_Y_ODDCHAR, in->input_split[w][in->idollar])
			&& !ft_strrchr(N_ODDCHAR, in->input_split[w][in->idollar]))
		{
			in->spaced = 1;
			while (in->input_split[w][*i] && in->input_split[w][*i] != '?')
				ft_printf("%c", in->input_split[w][(*i)++]);	
		}	
		if (in->input_split[w][*i] && in->input_split[w][*i] != '?')
			(*i)++;
		j++;
	}
	
	if (env_n < 0
		&& (ft_isalpha(in->input_split[w][in->idollar])
		|| in->input_split[w][in->idollar] == '_'))
		print_rest_no_env(in, w, i);
	else if (env_n == -1)
		print_rare_cases(in, w, i);
	else if (env_n == -2)
	{
		(*i)++;
		if (!(in->dollars % 2))
			ft_printf("%d", in->last_exit_code);
		else 
			ft_printf("?");
		while (in->input_split[w][*i] && in->input_split[w][*i] != '$')
		//&& in->input_split[w][(*i) + 1] != ' ' // por un error en echo "$?p " o "$? p"
			ft_printf("%c", in->input_split[w][(*i)++]);
	}
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
			print_invalid_envs(in, w, &i, in->env_n);
		}
		if (in->input_split[w][i] && in->input_split[w][i] != '$')
		{
			if (i > 0 && in->input_split[w][i] == ' ' 
				&& in->input_split[w][(i) - 1] == '$')
				ft_printf("%c", in->input_split[w][i]);
			i++;
		}
	}
}
