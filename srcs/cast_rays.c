/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufukuya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 23:34:30 by yufukuya          #+#    #+#             */
/*   Updated: 2020/08/09 19:22:59 by yufukuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	calculate_proj_wall_height(t_game *g, t_ray *ray)
{
	find_first_x_intersection(g, ray);
	find_horizontal_wall(g, ray);
	find_first_y_intersection(g, ray);
	find_vertical_wall(g, ray);
	if (ray->dist_to_horizontal_grid_being_hit <
			ray->dist_to_vertical_grid_being_hit)
		set_for_horizonta_wall(g, ray);
	else
		set_for_vertical_wall(g, ray);
	ray->distance /= g->units.fish[ray->cast_column];
	g->zbuffer[ray->cast_column] = ray->distance;
	ray->proj_wall_height = (g->wall_height *
			g->player.dist_to_pp / ray->distance);
}

void	cast_rays(t_game *g)
{
	t_ray ray;

	ray.cast_arc = g->player.arc;
	ray.cast_arc -= g->units.angle30;
	if (ray.cast_arc < 0)
		ray.cast_arc = g->units.angle360 + ray.cast_arc;
	ray.cast_column = 0;
	while (ray.cast_column < g->pp.width)
	{
		calculate_proj_wall_height(g, &ray);
		render_background_to_buffer(g, &ray);
		render_wall_to_buffer(g, &ray);
		ray.cast_column++;
		ray.cast_arc++;
		if (ray.cast_arc >= g->units.angle360)
			ray.cast_arc -= g->units.angle360;
	}
}
