/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:46:31 by jrollon-          #+#    #+#             */
/*   Updated: 2025/09/24 15:18:53 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

int	parse_color_component(const char *s, int *i)
{
	int	value;

	while (ft_isspace(s[*i]) || s[*i] == ',')
		(*i)++;
	value = ft_atoi(&s[*i]);
	if (ft_strlen(&s[*i]) == 0 || value < 0 || value > 255)
		return (-1);
	while (s[*i] && s[*i] != ',')
		(*i)++;
	return (value);
}

// Refactorización de tu función principal
void	save_color_in(const char *s, int *buf, int *count)
{
	int	i;
	int	r;
	int	g;
	int	b;

	i = 0;
	while (ft_isspace(s[i]))
		i++;
	r = parse_color_component(s, &i);
	g = parse_color_component(s, &i);
	b = parse_color_component(s, &i);
	if (r == -1 || g == -1 || b == -1)
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

/*
** Pone count espacios en un string nuevo y lo devuelve
*/
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

/*
** Hacw join de la línea y el padding y libera
*/
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
