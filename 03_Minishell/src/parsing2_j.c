/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2_j.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:38:35 by jrollon-          #+#    #+#             */
/*   Updated: 2025/06/02 11:44:30 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

void	quit_parsing(t_input *in, int stdout_save)
{
	close(stdout_save);
	clean_all(in, 1);
}

void	up_to_space(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	str[i] = '\0';
}

void	check_valid_redirections(char *str, size_t *i, size_t *final_redir)
{
	char	c;
	size_t	quotes;

	c = ' ';
	quotes = 0;
	while (str[*i])
	{
		if ((str[*i] == 0x1F) && !(quotes % 2))
		{
			c = str[*i];
			quotes++;
		}
		else if ((str[*i] == 0x1F) && c == str[*i])
		{
			c = ' ';
			quotes++;
		}
		if ((str[*i] == '<' || str[*i] == '>') && !(quotes % 2))
			*final_redir = *i;
		(*i)++;
	}
}

void	compose_command2(t_input *in, char *str, size_t final_redir)
{
	if (str[final_redir] && str[final_redir + 1])
	{
		if (in->split_exp[0] && in->split_exp[1])
		{
			free(in->command);
			in->command = ft_strdup(in->split_exp[1]);
		}
		if (!in->command)
			clean_all(in, 1);
	}
	else
	{
		if (in->split_exp[0] && in->split_exp[1] && in->split_exp[2])
		{
			free(in->command);
			in->command = ft_strdup(in->split_exp[2]);
		}
		if (!in->command)
			clean_all(in, 1);
	}
}

/*When < tk1 tk2 tk3 command will be tk2 and arg tk3."<" is not valid*/
/*char 0x1F is to ignore kk'>' token. So I write in compose token 0x1F char*/
/*...that is not used, to control that is like a quoted < or >*/
void	compose_command(t_input *in)
{
	size_t	i;
	size_t	final_redir;
	char	*str;

	i = 0;
	if (!in->split_exp)
		return ;
	str = in->split_exp[0];
	if ((str[0] == '<' || str[0] == '>') && in->status_exp[0] == 0)
	{
		check_valid_redirections(str, &i, &final_redir);
		compose_command2(in, str, final_redir);
		remove_control_char(in->command);
		up_to_space(in->command);
	}
}
