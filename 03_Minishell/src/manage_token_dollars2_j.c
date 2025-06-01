/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_token_dollars2_j.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 16:58:23 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/26 12:05:04 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

void	token_env_even_dollars_quo(t_input *in, size_t w, size_t *i,	size_t *k)
{
	size_t	j;

	if (!(in->dollars % 2))
	{
		j = 0;
		while (in->envp[in->env_n][j] != '=')
			j++;
		j++;
		while (in->envp[in->env_n][j])
		{
			dynamic_input(in, *k);
			in->token[(*k)++] = in->envp[in->env_n][j++];
		}
	}
	else
	{
		while (in->input_split[w][*i] && in->input_split[w][(*i) + 1] != ' ')
		{
			(*i)++;
			dynamic_input(in, *k);
			in->token[(*k)++] = in->input_split[w][(*i)];
		}
	}
}

/*will print the env if $USER or $$$USER. with $$USER will print USER that...*/
/*...is inside the else condition. that will stop up to the \0 or ' ' (if...*/
/*...inside of double quotes)*/
void	token_env_if_even_dollars(t_input *in, size_t w, size_t *i, size_t *k)
{
	size_t	j;

	if (!(in->dollars % 2))
	{
		j = 0;
		while (in->envp[in->env_n][j] != '=')
			j++;
		j++;
		while (in->envp[in->env_n][j] == ' ')
			j++;
		while (in->envp[in->env_n][j])
		{
			dynamic_input(in, *k);
			in->token[(*k)++] = in->envp[in->env_n][j++];
			/* if (in->envp[in->env_n][j] == ' ')
				break ; */
		}
		in->from_expand = 1;
	}
	else
	{
		while (in->input_split[w][*i] && in->input_split[w][(*i) + 1] != ' ')
		{
			(*i)++;
			dynamic_input(in, *k);
			in->token[(*k)++] = in->input_split[w][(*i)];
		}
	}
}

/*the second if is for cases like "$ a", $, where we are after the $ but...*/
/*...inside of double quotes or just nothing more, or course with EVEN $...*/
/*...again n->dollars % 2 == 0 is because we dont count the first $ found*/
void	token_valid_env_variable(t_input *n, size_t w, size_t *i, size_t *k)
{
	n->env_n = valid_env((n->input_split[w] + (*i) + 1), n, w);
	if (n->env_n > -1 && is_quoted(n, w) == 0)
		token_env_if_even_dollars(n, w, i, k);
	else if (n->env_n > -1 && is_quoted(n, w) == 2)
		token_env_even_dollars_quo(n, w, i, k);
	if (n->input_split[w][*i])
	{
		if (n->dollars % 2 == 0 && is_quoted(n, w) != 1 && n->env_n == -1
			&& (!n->input_split[w][n->idollar]
			|| n->input_split[w][n->idollar] == ' '))
		{
			dynamic_input(n, *k);
			n->token[(*k)++] = '$';
		}
		(*i)++;
	}
}

void	token_rest_no_env(t_input *in, size_t w, size_t *i, size_t *k)
{
	size_t	j;
	int		is_digit;
	char	*str;

	j = (*i);
	str = in->input_split[w];
	is_digit = ft_isdigit(str[in->idollar]);
	if (str[(*i)] && str[(*i) + 1] == ' ')
	{
		while (str[j] != '$')
		{
			if (is_digit || ft_strrchr(N_ODDCHAR, str[j])
				|| ft_strrchr(D_Y_ODDCHAR, str[j]))
				break ;
			j--;
		}
		if (str[j] != '$')
		{
			dynamic_input(in, *k);
			in->token[(*k)++] = in->input_split[w][(*i)];
		}
	}
}

/*save cases as $@p msg -> p msg or $%p msg -> $%p msg*/
/*when echo $$2p will save 2p. That is the (in->dollars % 2) case...*/
/*...it is ODD as we dont count the first $. So $$$$ are 3*/
void	token_rare_cases(t_input *in, size_t w, size_t *i, size_t *k)
{
	char	*str;
	size_t	id;

	id = in->idollar;
	str = in->input_split[w];
	if (in->dollars % 2)
	{
		dynamic_input(in, *k);
		in->token[(*k)++] = str[id];
		(*i) = id;
		return ;
	}
	dynamic_input(in, *k);
	if (!str[id] && in->input_split[w][*i])
		in->token[(*k)++] = '$';
	else if ((ft_isdigit(str[id]) || ft_strrchr(N_ODDCHAR, str[id])
			|| ft_strrchr(D_Y_ODDCHAR, str[id])) && str[id])
	{
		if (str[id] && !str[id + 1] && !ft_strrchr(D_Y_ODDCHAR, str[id]))
			in->spaced = 0;
		if (ft_strrchr(D_Y_ODDCHAR, str[id]))
		{
			in->token[(*k)++] = '$';
			dynamic_input(in, *k);
			in->token[(*k)++] = str[id];
		}
		(*i) = id;
	}
}
