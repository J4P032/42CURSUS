/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:46:31 by jrollon-          #+#    #+#             */
/*   Updated: 2025/09/30 13:22:47 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

int	parse_color_component(const char *s, int *i, int *colons)
{
	int	value;
	int	readed_chars;

	readed_chars = 0;
	while (s[(*i) + readed_chars] && s[(*i) + readed_chars] != '\n'
		&& s[(*i) + readed_chars] != ',')
	{
		if (!ft_isdigit(s[(*i) + readed_chars]))
			return (-1);
		readed_chars++;
	}
	if (readed_chars == 0)
		return (-1);
	value = ft_atoi(&s[*i]);
	if (value < 0 || value > 255)
		return (-1);
	while (s[*i] && s[*i] != ',')
		(*i)++;
	if (s[*i] == ',' && s[*i + 1])
	{
		(*i)++;
		(*colons)++;
	}
	return (value);
}

void	save_color_in(const char *s, int *buf, int *count)
{
	int	i;
	int	r;
	int	g;
	int	b;
	int	colons;

	i = 0;
	colons = 0;
	while (ft_isspace(s[i]))
		i++;
	r = parse_color_component(s, &i, &colons);
	g = parse_color_component(s, &i, &colons);
	b = parse_color_component(s, &i, &colons);
	if (r == -1 || g == -1 || b == -1 || colons != 2)
	{
		*buf = -1;
		return ;
	}
	*buf = (r << 16) | (g << 8) | b;
	*count += i - 1;
}

void	save_texture_in(char *s, char **buf, int *count)
{
	int	i;
	int	j;

	i = 0;
	if (!s || !buf)
		return ;
	while (ft_isspace(s[i]))
		i++;
	j = ft_strlen(s + i) - 1;
	while (j >= 0 && ft_isspace(s[i + j]))
		j--;
	if (*buf != NULL)
		free(*buf);
	*buf = ft_strndup(s + i, j + 1);
	*count += i + j + 1;
}

char	*make_padding(size_t count)
{
	char	*padding;
	size_t	i;

	padding = NULL;
	i = 0;
	padding = malloc(count + 1);
	if (!padding)
		return (NULL);
	while (i < count)
	{
		padding[i] = ' ';
		i++;
	}
	padding[i] = '\0';
	return (padding);
}

char	*join_and_replace(char *line, char *padding)
{
	char	*result;
	size_t	len;
	size_t	pad_len;

	result = NULL;
	len = ft_strlen(line);
	pad_len = ft_strlen(padding);
	result = malloc(len + pad_len + 1);
	if (!result)
	{
		free(line);
		free(padding);
		return (NULL);
	}
	ft_strcpy(result, line);
	ft_strcat(result, padding);
	free(line);
	free(padding);
	return (result);
}
