/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufukuya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 23:35:13 by yufukuya          #+#    #+#             */
/*   Updated: 2020/08/09 18:19:21 by yufukuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void		render_background_to_buffer(t_game *g, t_ray *ray)
{
	int row;
	int half;

	row = 0;
	half = g->pp.height / 2;
	while (row < half)
	{
		g->buf.data[row][ray->cast_column] = g->ceil_color;
		row++;
	}
	while (row < g->pp.height)
	{
		g->buf.data[row][ray->cast_column] = g->floor_color;
		row++;
	}
}

static void	set_top_and_bottom_of_wall(t_game *g, t_ray *ray)
{
	ray->bottom_of_wall = g->pp.y_center + (ray->proj_wall_height * 0.5);
	ray->top_of_wall = g->pp.y_center - (ray->proj_wall_height * 0.5);
	if (ray->top_of_wall < 0)
	{
		ray->top_of_wall = 0;
	}
	if (ray->bottom_of_wall >= g->pp.height)
	{
		ray->bottom_of_wall = g->pp.height - 1;
	}
}

static int	get_color_for_pos(t_game *g, t_ray *ray, int texture_y)
{
	int	color;
	int wall;
	int i;

	wall = 0;
	color = 0x000000;
	if (ray->wall_side == 'N')
		wall = NO_TEXTURE;
	else if (ray->wall_side == 'S')
		wall = SO_TEXTURE;
	else if (ray->wall_side == 'W')
		wall = WE_TEXTURE;
	else if (ray->wall_side == 'E')
		wall = EA_TEXTURE;
	i = g->tile_size * texture_y + (int)ray->x_offset;
	if (i >= g->buf.tex_size[wall])
		return (color);
	color = g->buf.textures[wall][i];
	if (ray->wall_side == 'W')
		color = (color >> 1) & 8355711;
	return (color);
}

void		render_wall_to_buffer(t_game *g, t_ray *ray)
{
	double	step_y;
	double	texture_position;
	int		texture_y;
	int		y;
	int		color;

	set_top_and_bottom_of_wall(g, ray);
	step_y = 1.0 * g->tile_size / ray->proj_wall_height;
	texture_position =
		(ray->top_of_wall - g->pp.height / 2 + ray->proj_wall_height / 2) *
		step_y;
	y = ray->top_of_wall;
	while (y <= ray->bottom_of_wall)
	{
		texture_y = (int)texture_position & (g->tile_size - 1);
		texture_position += step_y;
		color = get_color_for_pos(g, ray, texture_y);
		g->buf.data[y][ray->cast_column] = color;
		y++;
	}
}
