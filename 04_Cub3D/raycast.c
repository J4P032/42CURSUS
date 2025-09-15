/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 14:50:05 by jrollon-          #+#    #+#             */
/*   Updated: 2025/09/15 18:00:28 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*all Explanation for Raycasting comes from here:
https://lodev.org/cgtutor/raycasting.html */

/*
When we launch a ray from the player in any direction with an X and Y component
the first distance to reach the grid X or Y of each BOX (size 1) will be 
something not constant. BUT from that first X or Y grid, if we continue the ray
same direction, up to next X or Y grid, that distance will be constant forever.
THAT IS THE DeltaDist we want to calculate
https://lodev.org/cgtutor/images/raycastdelta.gif

That DeltaDist forms two triangles (blue=Xgrids, Green YGrids seen pin picture)
With Pythagoras Theorem: Hypotenuse = √(leg1² + leg2²)
That Hypotenuse is the delta_dist_x/y we want to calculate so:
(hypotenuse)delta_dist_x = √(legx² + legy²)

θ is the angle that the ray forms with the X-Axis so:
legx = 1 and tan(θ)=legy/legx -> legy=legx*tan(θ) = tan(θ) so...

delta_dist_x = √(1 + tan²(θ)) that is:

delta_dist_x² = (1 + rayDirY²/rayDirX²)=(rayDirX²/rayDirX²)+(rayDirY²/rayDirX²)
delta_dist_x² = (rayDirX² + rayDirY²) / rayDirX²

deltaDistX² = |rayDir|² / rayDirX² where |rayDir| is the longitude of vector so

deltaDistX = √(|rayDir|² / rayDirX²) = absolute(|rayDir| / rayDirX)

but because we look for the proportion of increase between X and Y that is...
the same always, we can substitute |rayDir| = 1 because the direction of 
the ray is usually normalized, because we look for the ratio between
its components (rayDirX and rayDirY) that would never change so we change the
scale of it to the basic 1:
deltaDistX = abs (1 / rayDirX) 

As can be seen there is a possible division by 0, so we set a practical
infinite = 1e32 = 1 x 10³²*/
void	set_const_ray_dist_between_grids(t_game *game)
{
	if (game->win->ray.dir_x == 0)
		game->win->ray.delta_dist_x = 1e32;
	else
		game->win->ray.delta_dist_x = fabs(1 / game->win->ray.dir_x);
	if (game->win->ray.dir_y == 0)
		game->win->ray.delta_dist_y = 1e32;
	else
		game->win->ray.delta_dist_y = fabs(1 / game->win->ray.dir_y);
}

/*step_x/y indicate direction the ray goes seen from up-down map (N-S-E-W)
if ray.dir_x > 0 -> step_x = 1 (goes to the EAST)
ray.dir_x < 0 -> step_x = -1 (goes WEST);
ray.dir_y > 0 -> step_y = 1 (goes SOUTH);
ray.dir_Y < 0 -> step_Y = -1 (goes NORTH);
we could use then same ray.dir_x/y, BUT step_x/y are INTs so we remove the
floating point in every 'step' that the ray make in same direction that will
run same delta_dist_x/y 

RAY.dist_x/y is the distance of the full ray already, BUT the first time is not
the delta one, it is shorter.  */
void	set_direction_of_ray(t_game *game)
{
	t_ray	*ray;

	ray = &game->win->ray;
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->dist_x = (game->map->p_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->dist_x = (ray->map_x + 1.0 - game->map->p_x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->dist_y = (game->map->p_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->dist_y = (ray->map_y + 1.0 - game->map->p_y) * ray->delta_dist_y;
	}
}

void	detect_wall_or_door(t_game *game)
{
	t_ray	*ray;

	ray = &game->win->ray;
	if (ray->map_y >= 0 && ray->map_y < (int)game->map->lines
			&& ray->map_x >= 0 && ray->map_x < (int)game->map->columns
			&& (game->map->map[ray->map_y][ray->map_x] == '1'
			|| game->map->map[ray->map_y][ray->map_x] == 'd'))
			{
				if (game->map->map[ray->map_y][ray->map_x] == 'd' && !ray->hit_door)
					ray->hit_door = 1;
				else
				{
					ray->hit = 1;
					ray->hit_tile = game->map->map[ray->map_y][ray->map_x];
				}
			}
}


/*Jump to next map square, either in x-direction, or in y-direction
the first if(RAY.dist_x <= RAY.dist_y) I set the == also to priorize the dist_x
distance so artifacts in corners are fixed.
it will increase distance each time to add the length of the ray.
Final if is to check if the ray is in the '1' (Wall) part so set HIT to 1.
side 0 -> the ray crosses vertical grid (X lines) and impact is EAST or WEST
side 1 -> Ray crosses horizontal grid lines (Y) impact is NORTH or SOUTH */
void	run_dda(t_game *game)
{
	t_ray	*ray;

	ray = &game->win->ray;
	while (ray->hit == 0)
	{
		if (ray->dist_x <= ray->dist_y)
		{
			ray->dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		detect_wall_or_door(game);
	}
}

/*
Calculate distance projected on camera plane. This is the shortest distance from
the point where the wall is hit to the camera plane. Euclidean to center camera\
point would give fisheye effect! 
https://lodev.org/cgtutor/images/raycastdist.png
This can be computed as 
(RAY.map_x - MAP->p_x + (1 - RAY.step_x) / 2) / RAY.dir_x for side == 0, 
or same formula with Y for size == 1,
but can be simplified to the code below thanks to how RAY.dist and delta_dist 
are computed:
because they were left scaled to |rayDir|. RAY.dist is the entire length of the
ray above after the multiple steps, but we subtract deltaDist once because
one step more into the wall was taken above before exiting the while no HIT.
https://lodev.org/cgtutor/images/raycastperpwalldist.png

To calculate the height of the line to be drawn depending on perspective
(RAY.line_height), we divide per RAY.perp_wall_dist because more distance
the object is, less drawing line is needed to be drawn it is inverse
proportional. If distance is < 1 then bigger would be.
We can multiply x factor to make taller objects. Right now is for 1:1

To calculate the init drawing pixel and end of that line:
Because the center of the wall is in the middle of the horizont line vision
the formula is as the code below to be equal distance of borders.

To calculate the pixels of the texture we need to know where impact the 
ray in U coordinates of the texture 0.0 to 1.0. So...
when we are side 0 (hit vertical walls), the X of the wall will be int as
it is over the same grid, but the Y not, so from the player add the 
distance to the collision (perp_wall_dist) through the ray sent (dir_y)
Same if side = 1 (horizontal walls) where we need to calculate in the Xs 
To have the fraction we use floor from math.h so for example if we have:
wallx = 3.75 -> floor(3.75) = 3.0 -> 3.75 - 3.0 = 0.75

I set an array of hit_dist to record the distance of each x of screen...
... width to compare with enemy sprite to hide behind wall corners*/
void	set_draw_length_without_fish_fx(t_game *game, int x)
{
	t_ray	*ray;

	ray = &game->win->ray;
	if (ray->side == 0)
	{
		ray->perp_wall_dist = ray->dist_x - ray->delta_dist_x;
		ray->wallx = game->map->p_y + ray->perp_wall_dist * ray->dir_y;
	}
	else
	{
		ray->perp_wall_dist = ray->dist_y - ray->delta_dist_y;
		ray->wallx = game->map->p_x + ray->perp_wall_dist * ray->dir_x;
	}
	ray->hit_dist[x] = ray->perp_wall_dist;
	ray->door_dist[x] = 0;
	ray->wallx = ray->wallx - floor(ray->wallx);
	ray->line_height = (int)((WIN_H / ray->perp_wall_dist) * WALL_HEIGHT);
	ray->draw_start = (-ray->line_height / 2) + (WIN_H / 2)
		+ ray->walking_height;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (ray->line_height / 2) + (WIN_H / 2) + ray->walking_height;
	if (ray->draw_end >= WIN_H)
		ray->draw_end = WIN_H - 1;
}

/*
1. camera_x will distribute WIN_W rays along all the CameraPlane. Value will be
   between -1 and 1 in floating point.
2. If we have a dir looking vector of (0, -1) (looking NORTH) for a FOV of...
   ...66° the fov_factor would be 0.66 so rotation to right of 90° the...
   ...looking direction (camera plane) would be (0.66, 0) Look map_2.c explain.
3. RAY.dir_X/Y are the direction (angle with looking dir) that the ray goes.
   for the most left ray in a looking (0, -1) vector that would be:
   RAY.dir_x = 0 + 0.66 * -1 = -0.66
   RAY.dir_y = -1 + 0 * -1 = -1
   So (-0.66, -1). Union of center of player to that point define the ray vector
4. RAY.map_x/y is the grid of the map we are.
5. With hit_door we detect the direct visual door from the character. The idea
   is to render the 'hidden' doors (behind other door) closed to allow...
   transparancy. Those 2nd doors are drawn in first pass. Doors to open in...
   second pass*/
void	raycaster(t_game *game, int x)
{
	double	factor;
	t_ray	*ray;

	factor = 0;
	ray = &game->win->ray;
	if (game->player.moving)
		factor = 0.005;
	if (game->player.running && game->player.moving)
		factor = 0.01;
	ray->hit = 0;
	ray->hit_door = 0;
	ray->camera_x = 2 * x / (double)WIN_W - 1 + ray->walking_wave * factor;
	ray->dir_x = game->map->dir_x + game->map->plane_x * ray->camera_x;
	ray->dir_y = game->map->dir_y + game->map->plane_y * ray->camera_x;
	ray->map_x = (int)game->map->p_x;
	ray->map_y = (int)game->map->p_y;
	set_const_ray_dist_between_grids(game);
	set_direction_of_ray(game);
	run_dda(game);
	set_draw_length_without_fish_fx(game, x);
	choose_color(game, x);
}
