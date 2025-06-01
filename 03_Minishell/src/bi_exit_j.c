/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit_j.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:16:14 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/27 01:59:52 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

int	valid_exit_quoted(t_input *in)
{
	size_t	token;
	size_t	i;

	token = in->word_after_arg - 1;
	i = 0;
	if (is_quoted(in, token) == 0)
		return (1);
	while (in->parsed[i] && in->parsed[i] == ' ')
		i++;
	if (in->parsed[i] == '+' || in->parsed[i] == '-')
		i++;
	if (!ft_isdigit(in->parsed[i]))
		return (0);
	while (ft_isdigit(in->parsed[i]))
		i++;
	while (in->parsed[i] && in->parsed[i] == ' ')
		i++;
	if (in->parsed[i] != '\0')
		return (0);
	return (1);
}

int	more_args(char *big, char *small)
{
	size_t	i;
	char	*aux;

	i = 0;
	aux = ft_strnstr(big, small, ft_strlen(big));
	while (aux[i] && aux[i] != ' ')
		i++;
	while (aux[i] && aux[i] == ' ')
		i++;
	if (aux[i] == '\0')
		return (0);
	return (1);
}

/*with error 1 from too many arguments bash dont exit with 2 yes it does*/
void	exit_miniyo(t_input *in, int num_exit)
{
	if (num_exit == 2)
	{
		ft_printf("exit\n");
		ft_putstr_fd("miniyo: exit: numeric argument required\n", 2);
	}
	clean_all(in, num_exit);
	if (num_exit == 0)
		rl_clear_history();
	exit(num_exit);
}

void	ft_exit(t_input *in)
{
	long long	arg;
	int			error;
	char		*code;

	error = 0;
	code = ft_first_word(in->parsed, ' ');
	if (in->parsed[0])
		arg = ft_atol(code, &error);
	else
		arg = in->last_exit_code;
	if (error || !valid_exit_quoted(in))
		exit_miniyo(in, 2);
	else
	{
		if (!more_args(in->parsed, code))
			exit_miniyo(in, arg & 0xFF);
		else
		{
			ft_putstr_fd("miniyo: exit: too many arguments\n", 2);
			in->last_exit_code = 1;
		}
	}
	free(code);
	code = NULL;
}
