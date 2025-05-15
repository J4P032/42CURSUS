/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_inputs_utils_j.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 09:31:56 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/15 21:33:07 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

int	save_valid_env_variable(t_input *n, size_t w, size_t *i, size_t *k)
{
	int		env_n;
	size_t	j;
	size_t 	start;

	env_n = valid_env((n->input_split[w] + (*i) + 1), n, w);
	if (env_n > -1)
	{
		if (!(n->dollars % 2))
		{
			j = 0;
			while (n->envp[env_n][j] != '=')
				j++;
			j++;
			while (n->envp[env_n][j] == ' ')
				j++;
			while (n->envp[env_n][j])
			{
				n->command[(*k)++] = n->envp[env_n][j++];
				if (n->envp[env_n][j] == ' ')
				{
					start = j;
					while (n->envp[env_n][j] == ' ')
					{
						if (n->envp[env_n][j] == '\0')
							break ;
						j++;
					}
					if (n->envp[env_n][j] != '\0')
						n->command[(*k)++] = ' ';
					j = start;
				}
				while (n->envp[env_n][j] == ' ')
					j++;
			}
		}
		else
		{
			while (n->input_split[w][*i] && n->input_split[w][(*i) + 1] != ' ')
			{
				(*i)++;
				n->command[(*k)++] = n->input_split[w][(*i)];
			}
		}
	}
	if (n->input_split[w][*i])
	{
		if(n->dollars % 2 == 0 && is_quoted(n, w) != 1 && env_n == -1
			&& (!n->input_split[w][n->idollar] || n->input_split[w][n->idollar] == ' ')) //"$ a", $, 
			n->command[(*k)++] = '$';
		(*i)++;
	}
	return (env_n);
}




void	save_rest_no_env(t_input *in, size_t w, size_t *i, size_t *k)
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
			in->command[(*k)++] = in->input_split[w][(*i)];
	}
}


void	save_rare_cases(t_input *in, size_t w, size_t *i, size_t *k)
{
	char	*str;
	size_t	index;
	
	index = in->idollar;
	str = in->input_split[w];
	if (in->dollars % 2 && in->input_split[w][*i])///anadido que sea distinto de cero
	{
		in->command[(*k)++] = str[index];
		(*i) = index;/////////////
		return ;
	}
	if (!str[index] && in->input_split[w][*i]) ///anadido que sea distinto de cero
		in->command[(*k)++] = '$';
	else if ((ft_isdigit(str[index]) || ft_strrchr(N_ODDCHAR, str[index])
		|| ft_strrchr(D_Y_ODDCHAR, str[index])) && str[index])
	{
		if (str[index] && !str[index + 1] && !ft_strrchr(D_Y_ODDCHAR, str[index]))
			in->spaced = 0;
		if (ft_strrchr(D_Y_ODDCHAR, str[index]))
		{
			in->command[(*k)++] = '$';
			in->command[(*k)++] = str[index];
		}	
		(*i) = index;
	}
}








void	save_invalid_envs(t_input *in, size_t w, size_t *i, size_t *k)
{
	size_t	env_len;
	size_t	j;
	size_t	l;
	char	*number;
	
	j = 0;
	l = 0;
	if (in->env_n > -1)
		env_len = validlen_env(in->envp[in->env_n], '=');
	else if (in->env_n == -1)
		env_len = invalidlen_env(in->input_split[w] + (*i));
	while (in->input_split[w][*i]
		&& in->input_split[w][(*i) + 1] != ' '
		&& in->input_split[w][*i] != '$'
		&& in->env_n != -2)
	{
		if (is_quoted(in, w) == 2 && in->input_split[w][*i] == '\'')
		{
			if (*i > 0)
				(*i)--;
			break ;
		}
		if (in->dollars > 0 && (in->dollars % 2) && (j < env_len)) //quiza poner && ((j < env_len) || ft_isdigit(in->input_split[in->idollar]) para el caso $$2 que tiene que ser 2
			in->command[(*k)++] = in->input_split[w][(*i)];
		else if (j >= env_len && !ft_isdigit(in->input_split[w][in->idollar])
			&& !ft_strrchr(D_Y_ODDCHAR, in->input_split[w][in->idollar])
			&& !ft_strrchr(N_ODDCHAR, in->input_split[w][in->idollar]))
		{
			in->spaced = 1;
			in->command[(*k)++] = in->input_split[w][(*i)];
		}	
		(*i)++;
		j++;
	}
	
	if (in->env_n < 0
		&& (ft_isalpha(in->input_split[w][in->idollar])
		|| in->input_split[w][in->idollar] == '_'))
		save_rest_no_env(in, w, i, k);
	else if (in->env_n == -1)
		save_rare_cases(in, w, i, k);
	else if (in->env_n == -2)
	{
		(*i)++;
		if (!(in->dollars % 2))
		{
			number = ft_itoa(in->last_exit_code);
			if (!number)
			{
				clean_all(in);
				exit (1);
			}
			while (number[l])
				in->command[(*k)++] = number[l++];
			free(number);
		}
		else 
			in->command[(*k)++] = '?';
		while (in->input_split[w][*i]
		&& in->input_split[w][(*i) + 1] != ' '
		&& in->input_split[w][*i] != '$')
			in->command[(*k)++] = in->input_split[w][(*i)++];
	}
}







void	save_if_spaced_and_valid_env(t_input *in, size_t w)
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
		space_after_first_invalid_env(in, w);
}


void	expand_dollar(t_input *in, size_t *i, size_t *j, size_t *k)
{
	save_if_spaced_and_valid_env(in, *i);
	in->dollars = 0;
	while (in->input_split[*i][*j])
	{
		if (in->input_split[*i][*j] != '$')
			in->command[(*k)++] = in->input_split[*i][(*j)];
		else
		{
			while (in->input_split[*i][(*j) + 1] == '$')
			{
			
				(*j)++;
				(in->dollars)++;
			}
			in->idollar = (*j) + 1;
			in->env_n = save_valid_env_variable(in, *i, j, k);
			save_invalid_envs(in, *i, j, k);
		
		
		
		
		}
		if (in->input_split[*i][*j] && in->input_split[*i][*j] != '$')
			(*j)++;
	}
}

void	search_dollar(t_input *in, size_t *i, size_t *j, size_t *k)
{
	int	print_as_env;
	
	print_as_env = (is_quoted(in, *i) == 2 || !is_quoted(in, *i));
	if (ft_strrchr(in->input_split[*i], '$') && print_as_env)
		expand_dollar(in, i, j, k);
	else
		in->command[(*k)++] = in->input_split[*i][(*j)++];
}


/*Do the same as copy_to_command BUT it starts from the token that was left...*/
/*...after the command. Because the token after the argument is behaved the...*/
/*...same as the first token in echo (no spaced unless quoted with space)...*/
/*...then we have to do the same with i < in this case word (after command)*/
void	copy_to_arg(t_input *in, size_t *i, size_t *j, size_t *k)
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
}

/*first if will stop copy when find a '' or "" that is previously spaced...*/
/*...if that token is not the first one as the first one will be always...*/
/*...spaced (because it is an argument). Could be (echo ''''-n'' example) */
/*The while inside will queck parts in quotes without space. If find an...*/
/*...space in the quotes will finish copy (echo '- n' -> no valid)...*/
/*...the if inside the internal while is a flag (in->spaced)to exit in...*/
/*...the botton if. Again i must be not the first word as it is spaced*/
void	copy_to_command(t_input *in, size_t *i, size_t *j, size_t *k)
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
				search_dollar(in, i, j, k);		
			in->status_checked = 1;
		}
		if (in->input_split[*i][*j] == ' ' || in->spaced)
			break ;
		(*i)++;
	}
}

void	compose_arg(t_input *in, size_t word)
{
	size_t	i;
	size_t	j;
	size_t	k;

	k = 0;
	i = word;
	in->word = word;
	in->spaced = 0;
	in->status_checked = 0;
	ft_bzero(in->args, 100000);
	copy_to_arg(in, &i, &j, &k);
	in->word_after_arg = i;
}

void	compose_command_args(t_input *in)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	in->spaced = 0;
	in->status_checked = 0;
	ft_bzero(in->command, 100000);
	copy_to_command(in, &i, &j, &k);
	in->word_after_command = i;
	compose_arg(in, i);
}
