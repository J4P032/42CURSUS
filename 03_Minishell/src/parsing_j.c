/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_j.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:33:24 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/30 01:24:23 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

void	up_to_space(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	str[i] = '\0';
}

/*When < tk1 tk2 tk3 command will be tk2 and arg tk3."<" is not valid*/
/*char 0x1F is to ignore kk'>' token. So I write in compose token the 0x1F char*/
/*...that is not used, to control that is like a quoted < or >*/
void	compose_command(t_input *in)
{
	size_t	i;
	size_t	final_redir;
	size_t	quotes;
	char	*str;
	char	c;

	i = 0;
	quotes = 0;
	if (!in->split_exp)
		return ;
	c = ' ';
	str = in->split_exp[0];
	if ((str[0] == '<' || str[0] == '>') && in->status_exp[0] == 0)
	{
		while (str[i])
		{
			if ((str[i] == 0x1F) && !(quotes % 2))
			{
				c = str[i];
				quotes++;
			}
			else if ((str[i] == 0x1F) && c == str[i])
			{	
				c = ' ';
				quotes++;
			}
			if ((str[i] == '<' || str[i] == '>') && !(quotes % 2))
				final_redir = i;
			i++;
		}
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
		remove_control_char(in->command);
		up_to_space(in->command);
	}
}

/*parsed returns with the command included. I need this to make expand env...*/
/*...with echo, So I need to clean the command from parsed and take the rest.*/
/*be carefull of spaces as we must include them in parsed I sustituted...*/
/*...while (in->parsed && in->parsed[i] == ' ') by an if to just run one space*/
void	write_parsed_output_from_file(t_input *in)
{
	char	*file;
	int		fd;
	char	*aux;
	size_t	i;

	i = 0;
	file = in->filename;
	fd = open(file, O_RDONLY);
	//ft_printf("fd: %d\n", fd);
	if (fd == -1)
		clean_all(in, 1);
	in->parsed = get_next_line(fd);
	aux = in->parsed;
	while (in->parsed && in->command && in->parsed[i] && in->command[i]
		&& in->parsed[i] == in->command[i])
		i++;
	if (in->parsed && in->parsed[i] == ' ')
		i++;
	if (in->parsed)
	{
		in->parsed = ft_strdup((in->parsed) + i);
		if (!in->parsed)
			clean_all(in, 1);
	}
	free(aux);
	close(fd);
	unlink(file);
}

char	*next_file(char *file, char **num, int *i, int *fd)
{
	(*i)++;
	free(file);
	free(*num);
	*num = ft_itoa(*i);
	if (!(*num))
		return (close(*fd), NULL);
	file = ft_strjoin("temp", *num);
	if (!file)
		return (close(*fd), free(*num), NULL);
	close(*fd);
	(*fd) = open(file, O_RDONLY);
	return (file);
}

char	*choose_name(void)
{
	int		fd;
	int		i;
	char	*number;
	char	*filename;

	i = 0;
	if (access(".", W_OK | R_OK) == -1)
		return (NULL);
	number = ft_itoa(i);
	if (!number)
		return (NULL);
	filename = ft_strjoin("temp", number);
	if (!filename)
		return (NULL);
	fd = open(filename, O_RDONLY);
	while (fd != -1)
	{
		filename = next_file(filename, &number, &i, &fd);
		if (!filename)
			return (NULL);
	}
	free(number);
	return (filename);
}

void	write_file(t_input *in, int fd, int stdout_save)
{
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		close(stdout_save);
		clean_all(in, 1);
	}
	ft_echo(in, 0);
	if (dup2(stdout_save, STDOUT_FILENO) == -1)
	{
		close(fd);
		close(stdout_save);
		clean_all(in, 1);
	}
	close(fd);
	close(stdout_save);
}

void	parsing(t_input *in)
{
	int		fd;
	int		stdout_save;
	size_t	i;

	i = 0;
	in->realloc_counter = 0;
	compose_token(in);
	compose_command(in);
	while (in->split_exp && in->split_exp[i])
		remove_control_char(in->split_exp[i++]);
	stdout_save = dup(STDOUT_FILENO);
	in->filename = choose_name();
	if (stdout_save == -1 || !in->filename)
	{
		if (!in->filename && stdout_save != 1)
			close(stdout_save);
		clean_all(in, 1);
	}
	fd = open(in->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		close(stdout_save);
		clean_all(in, 1);
	}
	write_file(in, fd, stdout_save);
	write_parsed_output_from_file(in);
}
