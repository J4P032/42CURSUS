/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo_short_j.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:24:00 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/27 17:47:16 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

int	is_valid_arg_(char *str)
{
	size_t	i;

	i = 1;
	if (!str)
		return (0);
	if (str[0] != '-')
		return (0);
	while (str[i] == 'n')
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

size_t	check_more_n(t_input *in)
{
	size_t	i;
	size_t	start;

	i = 0;
	while (in->parsed && in->parsed[i])
	{
		start = i;
		if (in->parsed[i] != '-')
			return (start);
		i++;
		while (in->parsed[i] && in->parsed[i] == 'n' && in->parsed[i] != ' ')
			i++;
		if (in->parsed[i] != ' ' && in->parsed[i] != '\0')
			return (start);
		if (in->parsed[i])
			i++;
	}	
	return (i);
}

/*depending on a variable exported that has -nnnn as an echo it will pass...*/
/*...them or not. So I will send that start point to write the parsed file*/
size_t	check_argument(t_input *in, int parsed_n)
{
	size_t	i;
	size_t	n_repeated;
	
	i = 1;
	n_repeated = 1;
	if (parsed_n)
		in->echo_error_n_arg = 0;
	if (!in->parsed[0])
		return (0);
	while (in->parsed[i] && in->parsed[i] != ' ')
	{
		if (in->parsed[i++] != 'n' || in->parsed[0] != '-')
		{
			n_repeated = 0;
			if (parsed_n)
				in->echo_error_n_arg = 1;
		}
	}
	if (ft_strncmp(in->parsed, "-n", 2) != 0 && parsed_n)
		in->echo_error_n_arg = 1;
	if (in->echo_error_n_arg == 0 && n_repeated)
		i = check_more_n(in);
	else
		i = 0;
	return (i);
}

/*if there is an > or < the msg that has to be echoed has to stop there...*/
/*or can be an parsed= >file echo msg that needs to be printed from echo.*/
/*But > or < came from exported VARS (input->status_exp = 2) will print > <*/
/*I search for first coincidence of echo (only or if come from exported VAR)..*/
/*...in split_aux*/
size_t	check_redirects(t_input *in, size_t start)
{
	size_t	i;
	char	*aux;
	char	*aux2;
	
	i = 0;
	aux = NULL;
	aux2 = NULL;
	while (in->split_exp && in->split_exp[i])
	{
		if (!ft_strncmp(in->split_exp[i], "echo", 4)
			&& (!in->split_exp[i][4] || in->status_exp[i] == 2))
			break ;
		i++;
	}
	if (!in->split_exp[i][4])
		aux = in->split_exp[i + 1];
	else if (in->status_exp[i] == 2)
		aux = &in->split_exp[i][5];
	if (aux && in->parsed)
		aux2 = ft_strnstr(in->parsed, aux, ft_strlen(in->parsed));
	i = 0;
	while (aux2 && in->parsed && in->parsed[i] && &in->parsed[i] != aux2)
		i++;
	if (start >= i)
		return start;
	return (i);
}

/*I want to check if the echo comes from $VAR or not. so that is the reason...*/
/*...of running the input to find first char appart from ' or ". If so, the...*/
/* -n that rules is the one in in->parsed*/
void	echo_short(t_input *in, int fd)
{
	int		parsed_n;
	size_t	start;
	size_t	i;
	
	i = 0;
	parsed_n = 0;
	while (in->input && (in->input[i] == '"' || in->input[i] == '\''))
		i++;
	if (in->input[i] == '$')
		parsed_n = 1;
	else if (in->args && in->args[0] == '$' && in->split_exp && in->split_exp[0]
		&& in->split_exp[1] && is_valid_arg_(in->split_exp[1]))
			parsed_n = 1;
	if (parsed_n)
		in->echo_error_n_arg = 1;
	start = check_argument(in, parsed_n);
	start = check_redirects(in, start);
	write(fd, in->parsed + start, ft_strlen(in->parsed + start));
	if (in->echo_error_n_arg == 1)
		write(fd, "\n", 1);
}
