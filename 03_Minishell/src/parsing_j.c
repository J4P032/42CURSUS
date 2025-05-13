/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_j.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:33:24 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/13 21:58:05 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

/*Do the same as copy_to_command BUT it starts from the token that was left...*/
/*...after the command. Because the token after the argument is behaved the...*/
/*...same as the first token in echo (no spaced unless quoted with space)...*/
/*...then we have to do the same with i < in this case word (after command)*/
/* void	copy_to_arg_b(t_input *in, size_t *i, size_t *j, size_t *k)
{
	while (*i < in->input_words)
	{
		*j = 0;
		in->status_checked = 0;
		if (*i > in->word && in->input_split[*i][0] == '\0'
			&& (in->status[*i] == SQUO_SP || in->status[*i] == DQUO_SP))
			break ;
		while ((in->input_split[*i][*j] != ' ' || is_quoted(in, *i))
			&& in->input_split[*i][*j] != '\0' && !in->spaced)
		{
			if ((*i > in->word && (in->status[*i] == EPTY_SP
						|| in->status[*i] == SQUO_SP
						|| in->status[*i] == DQUO_SP)
					&& !in->status_checked))
				in->spaced = 1;
			else
				in->args[(*k)++] = in->input_split[*i][(*j)++];
			in->status_checked = 1;
		}
		if (in->input_split[*i][*j] == ' ' || in->spaced)
			break ;
		(*i)++;
	}
} */

/*first if will stop copy when find a '' or "" that is previously spaced...*/
/*...if that token is not the first one as the first one will be always...*/
/*...spaced (because it is an argument). Could be (echo ''''-n'' example) */
/*The while inside will queck parts in quotes without space. If find an...*/
/*...space in the quotes will finish copy (echo '- n' -> no valid)...*/
/*...the if inside the internal while is a flag (in->spaced)to exit in...*/
/*...the botton if. Again i must be not the first word as it is spaced*/
/* void	copy_to_command_b(t_input *in, size_t *i, size_t *j, size_t *k)
{
	while (*i < in->input_words)
	{
		*j = 0;
		in->status_checked = 0;
		if (*i > 0 && in->input_split[*i][0] == '\0'
			&& (in->status[*i] == SQUO_SP || in->status[*i] == DQUO_SP))
			break ;
		while ((in->input_split[*i][*j] != ' ' || is_quoted(in, *i))
			&& (in->input_split[*i][*j] != '\0') && !in->spaced)
		{
			if (*i > 0 && (in->status[*i] == EPTY_SP
					|| in->status[*i] == SQUO_SP
					|| in->status[*i] == DQUO_SP)
				&& !in->status_checked)
				in->spaced = 1;
			else
				in->command[(*k)++] = in->input_split[*i][(*j)++];
			in->status_checked = 1;
		}
		if (in->input_split[*i][*j] == ' ' || in->spaced)
			break ;
		(*i)++;
	}
} */

/* void	compose_arg_b(t_input *in, size_t word)
{
	size_t	i;
	size_t	j;
	size_t	k;

	k = 0;
	i = word;
	in->word = word;
	in->spaced = 0;
	in->status_checked = 0;
	ft_bzero(in->args, 4096);
	copy_to_arg(in, &i, &j, &k);
	in->word_after_arg = i;
} */

/* void	compose_command_args_b(t_input *in)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	in->spaced = 0;
	in->status_checked = 0;
	ft_bzero(in->command, 250);
	copy_to_command(in, &i, &j, &k);
	in->word_after_command = i;
	compose_arg(in, i);
} */


void	create_node_parse(t_input *in)
{
	t_pars	*aux;
	t_pars	*new;
	
	new = (t_pars *)ft_calloc(1, sizeof(t_pars));
	if (!new)
	{
		clean_all(in);
		exit (1);//mirar si salgo con exit o no.
	}
	if (!in->parsed)
	{
		in->parsed = new;
		return ;
	}
	aux = in->parsed;
	while (aux->next)
		aux = aux->next;
	aux->next = new;
}


void	create_parse(t_input *in, size_t *i, size_t *j, size_t *k)
{
	size_t	start;
	size_t	n_chars;

	n_chars = 0;
	start = (*i);
	create_node_parse(in);
	while (*i < in->input_words)
	{
		*j = 0;
		in->status_checked = 0;
		if (*i > 0 && in->input_split[*i][0] == '\0'
			&& (in->status[*i] == SQUO_SP || in->status[*i] == DQUO_SP))
			break ;
		while ((in->input_split[*i][*j] != ' ' || is_quoted(in, *i))
			&& (in->input_split[*i][*j] != '\0') && !in->spaced)
		{
			if (*i > 0 && (in->status[*i] == EPTY_SP 
					|| in->status[*i] == SQUO_SP
					|| in->status[*i] == DQUO_SP)
				&& !in->status_checked)
				in->spaced = 1;
			else
			{
				(*j)++;
				n_chars++;
			}	
			in->status_checked = 1;
		}
		if (in->input_split[*i][*j] == ' ' || in->spaced)
			break ;
		(*i)++;
	}
	in->parsed->str = (char *)ft_calloc(n_chars + 1, sizeof(char));
	if (!in->parsed->str)
	{
		clean_all(in);
		exit(1);
	}
	*j = 0;
	while ((*k) < n_chars)
	{
		*j = 0;
		while (in->input_split[start][*j])
			in->parsed->str[(*k)++] = in->input_split[start][(*j)++];
		start++;
	}
}


void	parsing(t_input *in)
{
	size_t	i;
	size_t	j;
	size_t	k;

	k = 0;
	i = 0;
	in->spaced = 0;
	in->status_checked = 0;
	in->parsed = NULL;
	while (i < in->input_words)
	{
		create_parse(in, &i, &j, &k);
		k = 0;
		in->word = i;
		in->spaced = 0;
	}
	
	
	
	
	t_pars *aux = in->parsed;
	size_t	contador = 0;
	while (aux)
	{
		printf("%zu: %s\n", contador, aux->str);
		contador++;
		aux = aux->next;
	}
}
