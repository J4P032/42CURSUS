/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:55:02 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/05 14:24:38 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"
# include "./minilibx-linux/mlx.h"
# include <math.h>
# include <stdlib.h>

# define WIDTH 1920
# define HEIGHT 1080

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_x_pixel;
	int		line_length;
	int		endian;
}			t_data;

void	draw_window(void *mlx, void **window, t_data *image);
void	put_pixel(t_data *img, int x, int y, int color);
int	close_win(void *param);

#endif
