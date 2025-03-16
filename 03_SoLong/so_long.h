/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:55:02 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/16 14:00:51 by jrollon-         ###   ########.fr       */
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
# include <stdio.h>

//# define WIDTH 1920
//# define HEIGHT 1080
# define SPRITE_WIDTH 64
# define SPRITE_HEIGHT 64
# define NUM_SPRITES 10
# define SPRITES_ANIM 3
# define VALID_MAP_CHARS "CPE01\n"

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
	int			width;
	int			height;
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
	int		no_valid_char;
}			t_map;

typedef struct	s_game
{
	t_window	*win;
	t_map		*map;
}				t_game;

void	draw_window(t_game *game);
int		key_press(int key, t_game *game);
int		update_frame(t_game *game);
void	load_sprites(t_game *game);
void	load_pacman(t_game *game);
void	draw_map(t_game *game);
void	frame_map(t_game *game);
int		close_win(t_game *game);
t_map	*process_map(char *map);
void	load_map(t_map *map, char *map_dir);
char	*get_next_line(int fd);
void	clean_up_memory(t_game *game);
void	draw_sprite_on_canvas(t_game *game, t_sprite sprite, int x, int y);

#endif
