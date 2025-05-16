/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env_dollar_j.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:14:52 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/16 13:07:17 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

/*The function will return length of chars formed in and invalid env...*/
/* $a3cd_# = 5, $3ese_ = 0 */
/*if the first char is inside the ODDCHAR strings (rare chars) it will return*/
/*...cero. Also in case of ' ' ex. "$ p"*/
size_t	invalidlen_env(const char *str)
{
	size_t	i;

	i = 1;
	if (ft_isdigit(str[0]) || !str[0] || ft_strrchr(D_Y_ODDCHAR, str[0])
			|| ft_strrchr(N_ODDCHAR, str[0]) || str[0] == ' ') ///cuidado con ' ' que a lo mejor esta bien si es considerado luego con comillas dobles
		return (0);
	while (str && str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			break ;
		i++;
	}
	return (i);
}

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

void	print_rest_no_env(t_input *in, size_t w, size_t *i)
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
			ft_printf("%c", in->input_split[w][*i]);
	}
}

/*print cases as $@p msg -> p msg or $%p msg -> $%p msg*/
/*when echo $$2p will print 2p. That is the (in->dollars % 2) case...*/
/*...it is ODD as we dont count the first $. So $$$$ are 3*/
void	print_rare_cases(t_input *in, size_t w, size_t *i)
{
	char	*str;
	size_t	index;
	
	index = in->idollar;
	str = in->input_split[w];
	if (in->dollars % 2)// && in->input_split[w][*i])
	{
		ft_printf("%c", str[index]);
		(*i) = index;
		return ;
	}
	if (!str[index] && in->input_split[w][*i])
		ft_printf("$");
	else if ((ft_isdigit(str[index]) || ft_strrchr(N_ODDCHAR, str[index])
		|| ft_strrchr(D_Y_ODDCHAR, str[index])) && str[index])
	{
		if (str[index] && !str[index + 1] && !ft_strrchr(D_Y_ODDCHAR, str[index]))
			in->spaced = 0;
		if (ft_strrchr(D_Y_ODDCHAR, str[index]))
			ft_printf("$%c",str[index]);
		(*i) = index;
	}
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
	while (in->envp && in->envp[n])
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
