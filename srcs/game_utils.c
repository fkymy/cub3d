/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufukuya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 23:42:49 by yufukuya          #+#    #+#             */
/*   Updated: 2020/08/09 17:46:27 by yufukuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

double	arc_to_rad(t_game *g, int arc_angle)
{
	return ((arc_angle * M_PI) / g->units.angle180);
}

int		rad_to_arc(t_game *g, double rad)
{
	return (rad * g->units.angle180 / M_PI);
}

int		map_has_wall_at(t_game *g, double x, double y)
{
	int grid_index_x;
	int grid_index_y;

	grid_index_x = floor(x / g->tile_size);
	grid_index_y = floor(y / g->tile_size);
	if (grid_index_x >= g->grid.width || grid_index_y >= g->grid.height
		|| grid_index_x < 0 || grid_index_y < 0)
	{
		return (1);
	}
	if (g->grid.map[grid_index_y][grid_index_x] == '1')
		return (1);
	return (0);
}

double	distance_between_points(int x1, int x2, int y1, int y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
