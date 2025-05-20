/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_token_parsing_j.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 08:58:34 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/20 17:27:41 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"


void	copy_to_split_expanded(t_input *in, char *token, char ***split_exp)
{
	size_t	i;
	size_t	token_position;
	char	**new_token;

	i = 0;
	token_position = 0;
	while (*(split_exp) && (*split_exp)[token_position])
		token_position++;
	new_token = ft_calloc(token_position + 2, sizeof(char *));
	if (!new_token)
		clean_all(in, 1);
	while (i < token_position)
	{
		new_token[i] = ft_strdup((*split_exp)[i]);
		if (!new_token[i++])
			return (ft_matrix_free(new_token));
	}
	new_token[i] = ft_strdup(token);
	if (!new_token[i])
		return (ft_matrix_free(new_token));
	ft_matrix_free(*split_exp);
	*split_exp = new_token;
}


void	search_token_dollar(t_input *in, size_t *i, size_t *j, size_t *k)
{
	int	print_as_env;

	print_as_env = (is_quoted(in, *i) == 2 || !is_quoted(in, *i));
	if (ft_strrchr(in->input_split[*i], '$') && print_as_env)
		expand_token_dollar(in, i, j, k);
	else
	{
		in->token[(*k)++] = in->input_split[*i][(*j)++];
	}
}


/*first if will stop copy when find a '' or "" that is previously spaced...*/
/*...if that token is not the first one as the first one will be always...*/
/*...spaced (because it is an argument). Could be (echo ''''-n'' example) */
/*The while inside will queck parts in quotes without space. If find an...*/
/*...space in the quotes will finish copy (echo '- n' -> no valid)...*/
/*...the if inside the internal while is a flag (in->spaced)to exit in...*/
/*...the botton if. Again i must be not the first word as it is spaced*/
void	copy_to_token(t_input *in, size_t *i, size_t *j, size_t *k)
{
	while (*i < in->input_words)
	{
		*j = 0;
		in->status_checked = 0;
		if (*i > in->word && in->input_split[*i][0] == '\0'
			&& (in->status[*i] == SQUO_SP || in->status[*i] == DQUO_SP))
			break ;
		while ((in->input_split[*i][*j] != ' ' || is_quoted(in, *i))
			&& (in->input_split[*i][*j] != '\0') && !in->spaced)
		{
			if (*i > in->word && (in->status[*i] == EPTY_SP
					|| in->status[*i] == SQUO_SP
					|| in->status[*i] == DQUO_SP)
				&& !in->status_checked)
				in->spaced = 1;
			else
				search_token_dollar(in, i, j, k);
			in->status_checked = 1;
		}
		if (in->input_split[*i][*j]
			&& (in->input_split[*i][*j] == ' ' || in->spaced))
			break ;
		(*i)++;
	}
}

void	compose_token(t_input *in)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	counter;
	int		quoted;

	i = 0;
	counter = 0;
	ft_bzero(in->status_exp, 100);
	while (i < in->input_words)
	{
		k = 0;
		in->word = i;
		in->spaced = 0;
		in->status_checked = 0;
		ft_bzero(in->token, 100000);
		quoted = (is_quoted(in, i) == 2 || is_quoted(in, i) == 1);
		copy_to_token(in, &i, &j, &k);
		in->status_exp[counter] = quoted;
		counter++;
		copy_to_split_expanded(in, in->token, &in->split_exp);
	}
}







