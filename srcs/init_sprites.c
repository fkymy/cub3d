/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufukuya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 23:44:02 by yufukuya          #+#    #+#             */
/*   Updated: 2020/08/09 17:58:03 by yufukuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "game.h"
#include "allocation.h"

static void	add_sprite(t_game *g, int index, int row, int col)
{
	g->sprites[index].x = g->tile_size * col + (g->tile_size / 2);
	g->sprites[index].y = g->tile_size * row + (g->tile_size / 2);
	g->sprites[index].visible = 0;
	g->sprites[index].distance = 0;
	g->sprites[index].angle = 0;
	g->sprites[index].angle_diff = 0;
	g->sprites[index].arc_diff = 0;
	g->sprites[index].proj_height = 0;
	g->sprites[index].proj_width = 0;
	g->sprites[index].xcenter = 0;
	g->sprites[index].xstart = 0;
	g->sprites[index].xend = 0;
	g->sprites[index].ystart = 0;
	g->sprites[index].yend = 0;
}

static void	get_sprites_num(t_game *g, t_cub *cub)
{
	int i;
	int j;

	g->num_sprites = 0;
	i = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == '2')
			{
				g->num_sprites++;
			}
			j++;
		}
		i++;
	}
}

static int	init_zbuffer(t_game *g)
{
	if (!(g->sprite_order = (int *)ft_malloc(sizeof(int) * g->num_sprites)))
		return (INIT_SPRITES_ERR);
	if (!(g->zbuffer = (double *)ft_malloc(sizeof(double) * g->pp.width)))
		return (INIT_SPRITES_ERR);
	return (0);
}

static int	init_sprites_coordinates(t_game *g, t_cub *cub)
{
	int i;
	int j;
	int index;

	index = 0;
	if (!(g->sprites = (t_sprite *)ft_malloc(sizeof(t_sprite)
					* g->num_sprites)))
		return (INIT_SPRITES_ERR);
	i = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == '2')
			{
				add_sprite(g, index, i, j);
				index++;
			}
			j++;
		}
		i++;
	}
	return (0);
}

int			init_sprites(t_game *g, t_cub *cub)
{
	get_sprites_num(g, cub);
	if (init_zbuffer(g) == INIT_SPRITES_ERR)
		return (INIT_SPRITES_ERR);
	if (init_sprites_coordinates(g, cub) == INIT_SPRITES_ERR)
		return (INIT_SPRITES_ERR);
	return (0);
}
