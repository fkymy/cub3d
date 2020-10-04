/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufukuya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 23:43:26 by yufukuya          #+#    #+#             */
/*   Updated: 2020/08/09 17:56:09 by yufukuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "game.h"
#include "allocation.h"

void			modify_resolution(t_game *g)
{
	int sizex;
	int sizey;

	mlx_get_screen_size(g->mlx, &sizex, &sizey);
	if (g->pp.width > sizex)
	{
		g->pp.width = sizex;
	}
	if (g->pp.height > sizey)
	{
		g->pp.height = sizey;
		g->pp.y_center = g->pp.height / 2;
	}
}

void			init_unfailable_basic_info(t_game *g, t_cub *cub)
{
	g->tile_size = 64;
	g->wall_height = 64;
	g->grid.height = cub->map_height;
	g->grid.width = cub->map_width;
	g->grid.map = cub->map;
	g->grid.map[cub->start_row][cub->start_col] = '0';
	g->floor_color = cub->floor_rgba.r;
	g->floor_color = (g->floor_color << 8) + cub->floor_rgba.g;
	g->floor_color = (g->floor_color << 8) + cub->floor_rgba.b;
	g->ceil_color = cub->ceil_rgba.r;
	g->ceil_color = (g->ceil_color << 8) + cub->ceil_rgba.g;
	g->ceil_color = (g->ceil_color << 8) + cub->ceil_rgba.b;
	g->pp.width = cub->res_width;
	g->pp.height = cub->res_height;
	g->pp.y_center = g->pp.height / 2;
	modify_resolution(g);
}

int				init_unfailable_player_info(t_game *g, t_cub *cub)
{
	g->player.x = cub->start_col * 64 + 32;
	g->player.y = cub->start_row * 64 + 32;
	g->player.arc = g->units.angle0;
	if (cub->start_dir == 'E')
		g->player.arc = g->units.angle0;
	if (cub->start_dir == 'S')
		g->player.arc = g->units.angle90;
	if (cub->start_dir == 'W')
		g->player.arc = g->units.angle180;
	if (cub->start_dir == 'N')
		g->player.arc = g->units.angle270;
	g->player.dist_to_pp = (g->pp.width / 2) *
		g->units.tan_div[g->units.angle30];
	g->player.height = 32;
	g->player.speed = 6;
	return (0);
}

static int		init_buf(t_game *g)
{
	int i;
	int j;

	g->buf.data = (int **)ft_malloc(sizeof(int *) * g->pp.height);
	if (!g->buf.data)
		return (INIT_BUF_ERR);
	i = -1;
	while (++i < g->pp.height)
	{
		g->buf.data[i] = (int *)ft_malloc(sizeof(int) * g->pp.width);
		if (!g->buf.data[i])
			return (INIT_BUF_ERR);
	}
	i = -1;
	while (++i < g->pp.height)
	{
		j = -1;
		while (++j < g->pp.width)
			g->buf.data[i][j] = 0;
	}
	return (0);
}

void			init_game(t_game *g, t_cub *cub)
{
	int err;

	err = 0;
	init_unfailable_basic_info(g, cub);
	err |= init_units(g);
	init_unfailable_player_info(g, cub);
	err |= init_buf(g);
	err |= init_texture(g, cub);
	err |= init_sprites(g, cub);
	if (err)
	{
		ft_putstr_fd("Error\n", 1);
		exit_free("Failed to initialize game.\n");
	}
}
