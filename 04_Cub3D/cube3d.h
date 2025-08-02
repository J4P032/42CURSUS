/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:00:38 by jrollon-          #+#    #+#             */
/*   Updated: 2025/08/02 14:42:26 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H
# include "libft/libft.h"
# include "./minilibx-linux/mlx.h"
# include <math.h>
# include <stdio.h>
//# include <unistd.h>
//# include <stdlib.h>
//# include <stdlib.h>

# define TEXTURE_W 512
# define TEXTURE_H 512
# define PI 3.14159265358979323846
# define FOV 66 //degrees
# define NUM_SPRITES 0
# define VALID_MAP_CHARS "NSEW01\n"

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_x_pixel;
	int		line_length;
	int		endian;
}			t_data;

/* typedef struct s_sprite
{
	t_data	img[SPRITES_ANIM];
	int		x;
	int		y;
	int		i;
	int		j;
	int		prev_i;
	int		prev_j;
	int		go_right;
	int		go_down;
	int		go_left;
	int		go_up;
	int		desired_dir;
	size_t	distance;
	int		width;
	int		height;
	char	*bitmap[SPRITES_ANIM];
}			t_sprite; */

typedef struct s_window
{
	void		*mlx;
	void		*win;
	t_data		canvas;
	t_data		buffer;
	int			width;
	int			height;
	int			running;
	//t_sprite	sprite[NUM_SPRITES];
}				t_window;

typedef struct s_map
{
	char	**map;
	size_t	columns;
	size_t	lines;
	int		num_p;
	double	p_x;
	double	p_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	
	//int		num_c;
	//int		check_c;
	//int		num_e;
	//int		check_e;
	int		num_walls;
	int		no_rectangle;
	int		no_valid_char;
}			t_map;

typedef struct s_game
{
	t_window	*win;
	t_map		*map;
}				t_game;

void	clean_up_memory(t_game *game);
int		close_win(t_game *game);
void	draw_window(t_game *game);
t_map	*process_map(char *map_dir);
void	load_map(t_map *map, char *map_dir);
void	init_looking_direction(t_map *map, char c);

//# define SPRITES_ANIM 3
//# define VALID_MAP_CHARS "CPE01\n"

/* 
int		key_press(int key, t_game *game);
int		update_frame(t_game *game);
void	load_sprites(t_game *game);
void	load_pacman(t_game *game);
void	load_collect(t_game *game);
void	load_exit(t_game *game);
void	pacman_iddle(t_game *game);
void	pacman_eat(t_game *game);
void	pre_movement(t_game *game);
void	draw_map(t_game *game);
void	frame_map(t_game *game);
void	frame_collect(t_game *game);
void	frame_exit(t_game *game);
int		scale_time(int *num, int time);
int		only_once(int *num, int time);
t_map	*process_map(char *map);
int		check_map_solution(t_map *map);
void	load_map(t_map *map, char *map_dir);
char	*get_next_line(int fd);
void	draw_sprite_on_canvas(t_game *game, t_sprite sprite, int x, int y);
void	collect_sprite_anim(t_game *game, int x, int y);
void	delay_time(t_game *game, double time);
void	where_is_pacman(t_game *game);
void	count_movements(t_game *game);
void	check_ber(char *map_dir); */

#endif
