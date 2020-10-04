/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_units_calc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufukuya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 23:45:43 by yufukuya          #+#    #+#             */
/*   Updated: 2020/08/07 23:45:55 by yufukuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	calc_trig(t_game *g, int i)
{
	double radian;

	radian = arc_to_rad(g, i) + (0.000001);
	g->units.sin[i] = sin(radian);
	g->units.sin_div[i] = 1.0 / g->units.sin[i];
	g->units.cos[i] = cos(radian);
	g->units.cos_div[i] = 1.0 / g->units.cos[i];
	g->units.tan[i] = tan(radian);
	g->units.tan_div[i] = 1.0 / g->units.tan[i];
}

void	calc_horizontal_xstep(t_game *g, int i)
{
	if (i >= g->units.angle90 && i < g->units.angle270)
	{
		g->units.horizontal_xstep[i] = g->tile_size / g->units.tan[i];
		if (g->units.horizontal_xstep[i] > 0)
			g->units.horizontal_xstep[i] *= -1;
	}
	else
	{
		g->units.horizontal_xstep[i] = g->tile_size / g->units.tan[i];
		if (g->units.horizontal_xstep[i] < 0)
			g->units.horizontal_xstep[i] *= -1;
	}
}

void	calc_vertical_ystep(t_game *g, int i)
{
	if (i >= g->units.angle0 && i < g->units.angle180)
	{
		g->units.vertical_ystep[i] = g->tile_size * g->units.tan[i];
		if (g->units.vertical_ystep[i] < 0)
			g->units.vertical_ystep[i] *= -1;
	}
	else
	{
		g->units.vertical_ystep[i] = g->tile_size * g->units.tan[i];
		if (g->units.vertical_ystep[i] > 0)
			g->units.vertical_ystep[i] *= -1;
	}
}
