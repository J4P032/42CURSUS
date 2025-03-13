/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:55:02 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/13 14:18:21 by jrollon-         ###   ########.fr       */
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
# include <X11/keysym.h>
//# include <X11/keysymdef.h>
//# include <X11/X.h>

# define WIDTH 1920
# define HEIGHT 1080
# define NUM_SPRITES 5
# define SPRITES_ANIM 3
# define PI 3.141592

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_x_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_sprite
{
	t_data	img[SPRITES_ANIM];
	int		x;
	int		y;
	int		go_right;
	int		go_down;
	int		go_left;
	int		go_up;
	int		width;
	int		height;
	char	*bitmap[SPRITES_ANIM];
}			t_sprite;

typedef struct s_window
{
	void		*mlx;
	void		*win;
	t_data		canvas;
	t_data		buffer;
	int			x;
	int			y;
	float		angle;
	int			running;
	t_sprite	sprite[NUM_SPRITES];
}				t_window;

typedef struct s_map
{
	char	**map;
	size_t	columns;
	size_t	lines;
	int		num_p;
	int		num_c;
	int		num_e;
	int		num_walls;
	int		no_rectangle;
}			t_map;

void	draw_window(t_window *win);
int		key_press(int key, t_window *win);
int		update_frame(t_window *win);
void	put_pixel(t_data *img, int x, int y, int color);
void	load_pacman(t_window *win);
int		close_win(void *param);
t_map	*process_map(char *map);
char	*get_next_line(int fd);

#endif
