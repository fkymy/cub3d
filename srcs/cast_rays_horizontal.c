/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays_horizontal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufukuya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 23:36:01 by yufukuya          #+#    #+#             */
/*   Updated: 2020/08/09 18:27:06 by yufukuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void		find_first_x_intersection(t_game *g, t_ray *ray)
{
	if (ray->cast_arc > g->units.angle0 && ray->cast_arc < g->units.angle180)
	{
		ray->horizontal_grid = floor(g->player.y / g->tile_size) *
			g->tile_size + g->tile_size;
		ray->dist_to_next_horizontal_grid = g->tile_size;
		ray->x_intersection = g->units.tan_div[ray->cast_arc] *
			(ray->horizontal_grid - g->player.y);
		ray->x_intersection += g->player.x;
	}
	else
	{
		ray->horizontal_grid = floor(g->player.y / g->tile_size) *
			g->tile_size;
		ray->dist_to_next_horizontal_grid = -g->tile_size;
		ray->x_intersection = g->units.tan_div[ray->cast_arc] *
			(ray->horizontal_grid - g->player.y);
		ray->x_intersection += g->player.x;
		ray->horizontal_grid--;
	}
}

static void	step_until_wall(t_game *g, t_ray *ray)
{
	while (1)
	{
		ray->x_grid_index = floor(ray->x_intersection / g->tile_size);
		ray->y_grid_index = floor(ray->horizontal_grid / g->tile_size);
		if (ray->x_grid_index >= g->grid.width ||
				ray->y_grid_index >= g->grid.height ||
				ray->x_grid_index < 0 || ray->y_grid_index < 0)
		{
			ray->dist_to_horizontal_grid_being_hit = INT_MAX;
			break ;
		}
		else if (g->grid.map[ray->y_grid_index][ray->x_grid_index] == '1')
		{
			ray->dist_to_horizontal_grid_being_hit =
				(ray->x_intersection - g->player.x) *
				g->units.cos_div[ray->cast_arc];
			break ;
		}
		else
		{
			ray->x_intersection += ray->dist_to_next_x_intersection;
			ray->horizontal_grid += ray->dist_to_next_horizontal_grid;
		}
	}
}

void		find_horizontal_wall(t_game *g, t_ray *ray)
{
	if (ray->cast_arc == g->units.angle0 || ray->cast_arc == g->units.angle180)
	{
		ray->dist_to_horizontal_grid_being_hit = INT_MAX;
	}
	else
	{
		ray->dist_to_next_x_intersection =
			g->units.horizontal_xstep[ray->cast_arc];
		step_until_wall(g, ray);
	}
}

void		set_for_horizonta_wall(t_game *g, t_ray *ray)
{
	ray->distance = ray->dist_to_horizontal_grid_being_hit;
	if (ray->cast_arc >= g->units.angle0 && ray->cast_arc < g->units.angle180)
	{
		ray->wall_side = 'N';
	}
	else
	{
		ray->wall_side = 'S';
	}
	ray->x_offset = fmod(ray->x_intersection, g->tile_size);
}
