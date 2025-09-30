/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:28:47 by marcoga2          #+#    #+#             */
/*   Updated: 2025/09/30 14:27:29 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ends_with_cub(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	return (len >= 4 && ft_strcmp(filename + len - 4, ".cub") == 0);
}

int	is_valid(const char *path)
{
	int		fd;
	int		error;
	char	buf[1];
	ssize_t	bytes_read;

	error = 0;
	if (!ends_with_cub(path))
		error = printf("Error\nFile must have a .cub extension\n");
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		if (errno == ENOENT)
			error = printf("Error\nFile does not exist\n");
		else if (errno == EISDIR)
			error = printf("Error\n'%s' is a directory\n", path);
		else
			error = printf("Error\nCannot open file for reading\n");
		return (error == 0);
	}
	bytes_read = read(fd, buf, 1);
	if (bytes_read == 0)
		error = printf("Error\nMap file is empty\n");
	close(fd);
	return (error == 0);
}
