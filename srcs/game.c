/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufukuya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 23:42:11 by yufukuya          #+#    #+#             */
/*   Updated: 2020/10/04 14:09:17 by yufukuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "allocation.h"

t_game	*game_new(void)
{
	t_game *g;

	g = (t_game *)ft_malloc(sizeof(t_game));
	ft_bzero(g, sizeof(t_game));
	return (g);
}

void	render(t_game *g)
{
	int row;
	int col;

	row = 0;
	while (row < g->pp.height)
	{
		col = 0;
		while (col < g->pp.width)
		{
			g->img.data[row * (g->img.size_l / 4) + col] =
				g->buf.data[row][col];
			col++;
		}
		row++;
	}
	mlx_do_sync(g->mlx);
	mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
}

int		game_loop(t_game *g)
{
	cast_rays(g);
	// cast_sprites(g);
	render(g);
	return (0);
}
