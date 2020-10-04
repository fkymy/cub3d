/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays_vertical.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufukuya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 23:36:32 by yufukuya          #+#    #+#             */
/*   Updated: 2020/08/09 18:27:39 by yufukuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void		find_first_y_intersection(t_game *g, t_ray *ray)
{
	if (ray->cast_arc < g->units.angle90 ||
			ray->cast_arc > g->units.angle270)
	{
		ray->vertical_grid = g->tile_size +
			floor(g->player.x / g->tile_size) * g->tile_size;
		ray->dist_to_next_vertical_grid = g->tile_size;
		ray->y_intersection = g->units.tan[ray->cast_arc] *
			(ray->vertical_grid - g->player.x);
		ray->y_intersection += g->player.y;
	}
	else
	{
		ray->vertical_grid = floor(g->player.x / g->tile_size) *
			g->tile_size;
		ray->dist_to_next_vertical_grid = -g->tile_size;
		ray->y_intersection = g->units.tan[ray->cast_arc] *
			(ray->vertical_grid - g->player.x);
		ray->y_intersection += g->player.y;
		ray->vertical_grid--;
	}
}

static void	step_until_wall(t_game *g, t_ray *ray)
{
	while (1)
	{
		ray->x_grid_index = floor(ray->vertical_grid / g->tile_size);
		ray->y_grid_index = floor(ray->y_intersection / g->tile_size);
		if (ray->x_grid_index >= g->grid.width ||
				ray->y_grid_index >= g->grid.height ||
				ray->x_grid_index < 0 || ray->y_grid_index < 0)
		{
			ray->dist_to_vertical_grid_being_hit = INT_MAX;
			break ;
		}
		else if (g->grid.map[ray->y_grid_index][ray->x_grid_index] == '1')
		{
			ray->dist_to_vertical_grid_being_hit =
				(ray->y_intersection - g->player.y) *
				g->units.sin_div[ray->cast_arc];
			break ;
		}
		else
		{
			ray->y_intersection += ray->dist_to_next_y_intersection;
			ray->vertical_grid += ray->dist_to_next_vertical_grid;
		}
	}
}

void		find_vertical_wall(t_game *g, t_ray *ray)
{
	if (ray->cast_arc == g->units.angle90 ||
			ray->cast_arc == g->units.angle270)
	{
		ray->dist_to_vertical_grid_being_hit = INT_MAX;
	}
	else
	{
		ray->dist_to_next_y_intersection =
			g->units.vertical_ystep[ray->cast_arc];
		step_until_wall(g, ray);
	}
}

void		set_for_vertical_wall(t_game *g, t_ray *ray)
{
	ray->distance = ray->dist_to_vertical_grid_being_hit;
	if (ray->cast_arc >= g->units.angle90 && ray->cast_arc < g->units.angle270)
	{
		ray->wall_side = 'E';
	}
	else
	{
		ray->wall_side = 'W';
	}
	ray->x_offset = fmod(ray->y_intersection, g->tile_size);
}
