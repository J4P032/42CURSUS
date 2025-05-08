/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env_dollar_j.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:14:52 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/09 00:10:01 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

size_t	ft_envlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

size_t	ft_strlen_quoted(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	return (i);
}

/*if not found will return 0, if found will return the number of env variable*/
/*can be the same up to size of env (from 0 to =), but str can be more so...*/
/*...not valid unless end $. Ex: $USERpotato. USER is 4 but USERpotato more...*/
/*...$USER$ is valid and $USER$USER$ also*/
int	valid_env(const char *str, t_input *in, size_t w)
{
	size_t	n;
	size_t	envlen;
	int		dqu;

	n = 0;
	if (!str)
		return (-1);
	dqu = (in->status[w] == DQUO_SP || in->status[w] == DQUO_NSP);
	while (in->envp[n])
	{
		envlen = ft_envlen(in->envp[n]);
		if (!ft_strncmp(in->envp[n], str, envlen))
		{
			if (dqu && (ft_strlen_quoted(str) == envlen || str[envlen] == '$'))
				return (n);
			else if (!dqu && (ft_strlen(str) == envlen || str[envlen] == '$'))
				return (n);
		}
		n++;
	}
	return (-1);
}
