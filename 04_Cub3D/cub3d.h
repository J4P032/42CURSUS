/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 14:50:42 by jrollon-          #+#    #+#             */
/*   Updated: 2025/08/05 09:21:36 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libft/libft.h"
# include "./minilibx-linux/mlx.h"
# include <math.h>
# include <stdio.h>
//# include <unistd.h>
//# include <stdlib.h>
//# include <stdlib.h>

# define WIN_W 1024
# define WIN_H 768
# define TEXTURE_W 512
# define TEXTURE_H 512
# define PI 3.14159265358979323846
# define FOV 66 //degrees. Will affect also WALL_HEIGHT perception
# define WALL_HEIGHT 1
# define NUM_SPRITES 0
# define MOVE_SPEED 0.02
# define ROTATION_SPEED 2
# define VALID_MAP_CHARS "NSEW01\n"
# define RAY (game->win->ray)
# define MAP (game->map)
# define CANVAS (game->win->canvas)
# define KEY (game->keys)
# define PLAYER (game->player)

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

typedef struct s_ray
{
	double	camera_x; //where the ray will be launch in cameraX coordinates
	double	dir_x; //component in X of the ray
	double	dir_y;
	double	dist_x; //distance of the ray to next X grid in X component
	double	dist_y;
	double	delta_dist_x; //constant distance the ray runs to travel full X grid
	double	delta_dist_y;
	double	perp_wall_dist; //perpendicular distance to camera plane from hit
	int		map_x; //where the player is in the map grid X
	int		map_y;
	int		step_x; //direction of ray going. 1=Right, -1=Left
	int		step_y; //direction of ray going. 1=Down(0,0 on topLeft), -1=UP
	int		hit; //0 ray no hit, 1 hit something
	int		side; //side of hit. 0=WE side, 1=NS side
	int		line_height; //how much to render the line of wall (or enemy)
	int		draw_start; //start of pixel draw in Y above the horizont (width/2)
	int		draw_end; //end of pixel draw in vertical Y.
	int		color;
	int		walking_height;
	int		walking_wave;//
	double	i_walking;
	double	fov_factor;
} 			t_ray;

typedef struct s_window
{
	void		*mlx;
	void		*win;
	t_data		canvas;
	t_data		buffer;
	int			width;
	int			height;
	int			running;
	t_ray		ray;
	//t_sprite	sprite[NUM_SPRITES];
}				t_window;

typedef struct s_map
{
	char	**map;
	size_t	columns;
	size_t	lines;
	int		num_p;
	double	p_x; //position of the player in X component
	double	p_y;
	double	dir_x; //direction in X, main character is looking
	double	dir_y;
	double	plane_x; //Plane perpendicular to looking direction
	double	plane_y;
	
	int		num_walls;
	int		no_rectangle;
	int		no_valid_char;
}			t_map;

typedef	struct s_keys
{
	int w;
	int	s;
	int	a;
	int	d;
	int left;
	int right;
	int space;
	int	shift;
}		t_keys;

typedef struct s_player
{
	int		moving;
	int		running;
	double	i_wave_walk;
}			t_player;


typedef struct s_game
{
	t_window	*win;
	t_map		*map;
	t_keys		keys;
	t_player	player;
}				t_game;

void	clean_up_memory(t_game *game);
int		close_win(t_game *game);
void	draw_window(t_game *game);
t_map	*process_map(char *map_dir);
void	load_map(t_map *map, char *map_dir);
void	init_looking_direction(t_map *map, char c);
int		update_frame(t_game *game);
void	raycaster(t_game *game, int x);
void	choose_color(t_game *game);
void	put_pixel(t_data *img, int x, int y, int color);
void	keys_movement(t_game *game);
int		key_press(int key, t_game *game);
int		key_release(int key, t_game *game);
void	rotate_camera(t_game *game, int direction);

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
