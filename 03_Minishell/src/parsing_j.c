/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_j.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:33:24 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/20 20:07:56 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

/*When < token1 token2 token3 command will be token2 and arg token3."<" is...*/
/*...not valid*/
void	compose_command(t_input *in)
{	
	if (in->split_exp
		&& (in->split_exp[0][0] == '<' || in->split_exp[0][0] == '>')
		&& in->status_exp[0] == 0)
	{
		if (in->split_exp[0] && in->split_exp[1] && in->split_exp[2])
			ft_strlcpy(in->command, in->split_exp[2], ft_strlen(in->split_exp[2]) + 1);

		if (in->split_exp[0] && in->split_exp[1] && in->split_exp[2]
			&& in->split_exp[3])
			ft_strlcpy(in->args, in->split_exp[3], ft_strlen(in->split_exp[3]) + 1);
	}
	/* else
	{
		if (in->split_exp && in->split_exp[0] && in->split_exp[1])
			ft_strlcpy(in->args, in->split_exp[1], ft_strlen(in->split_exp[1]));	
	} */
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
	if (fd == -1)
		clean_all(in, 1);
	in->parsed = get_next_line(fd);
	aux = in->parsed;
	while (in->parsed && in->parsed[i] && in->parsed[i] != ' ')
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

	compose_token(in);
	compose_command(in);///
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
