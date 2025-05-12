/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env_dollar_j.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:14:52 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/12 20:02:11 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

/*will determine de length of the str depending of the ending c char*/
/*will receive or \0 or ' '. Space when is double quoted*/
/*if I give it c = '=' is for determine the length of the real env variable*/
size_t	validlen_env(const char *str, char c)
{
	size_t	i;

	i = 0;
	while (str && str[i] && str[i] != c)
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			break ;
		i++;
	}
	return (i);
}

/*if not found will return -1, if found will return the number of env variable*/
/*can be the same up to size of env (from 0 to =), but str can be more so...*/
/*...not valid unless end $. Ex: $USERpotato. USER is 4 but USERpotato more...*/
/*...$USER$ is valid and $USER$USER$ also*/
/*Will return -2 when we find a ? after the $ to manage the exit codes.*/
int	valid_env(const char *str, t_input *in, size_t w)
{
	size_t	n;
	size_t	envlen;
	int		dqu;

	n = 0;
	if (!str)
		return (-1);
	dqu = (in->status[w] == DQUO_SP || in->status[w] == DQUO_NSP);
	if (str[0] == '?')
		return (-2);
	while (in->envp[n])
	{
		envlen = validlen_env(in->envp[n], '=');
		if (!ft_strncmp(in->envp[n], str, envlen))
		{
			if (dqu && (validlen_env(str, ' ') == envlen || str[envlen] == '$'))
				return (n);
			else if (!dqu && (validlen_env(str, '\0') == envlen || str[envlen] == '$'))
				return (n);
		}
		n++;
	}
	return (-1);
}
