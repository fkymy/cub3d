/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_units.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufukuya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 23:45:05 by yufukuya          #+#    #+#             */
/*   Updated: 2020/08/09 18:00:21 by yufukuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "game.h"
#include "allocation.h"

static void	init_angles(t_game *g)
{
	g->units.angle60 = g->pp.width;
	g->units.angle30 = floor(g->units.angle60 / 2);
	g->units.angle15 = floor(g->units.angle30 / 2);
	g->units.angle90 = floor(g->units.angle30 * 3);
	g->units.angle180 = floor(g->units.angle90 * 2);
	g->units.angle270 = floor(g->units.angle90 * 3);
	g->units.angle360 = floor(g->units.angle60 * 6);
	g->units.angle0 = 0;
	g->units.angle1 = floor(g->units.angle5 / 5);
	g->units.angle5 = floor(g->units.angle30 / 6);
	g->units.angle10 = floor(g->units.angle5 * 2);
	g->units.angle45 = floor(g->units.angle15 * 3);
}

static int	init_fish(t_game *g)
{
	int		i;
	double	radian;

	if (!(g->units.fish = ft_malloc(sizeof(double) * (g->units.angle60 + 1))))
		return (INIT_UNITS_ERR);
	i = -g->units.angle30;
	while (i <= g->units.angle30)
	{
		radian = arc_to_rad(g, i);
		g->units.fish[i + g->units.angle30] = 1.0 / cos(radian);
		i++;
	}
	return (0);
}

static int	init_trig(t_game *g)
{
	if (!(g->units.sin = ft_malloc(sizeof(double) *
					(g->units.angle360 + 1))))
		return (INIT_UNITS_ERR);
	if (!(g->units.sin_div = ft_malloc(sizeof(double) *
					(g->units.angle360 + 1))))
		return (INIT_UNITS_ERR);
	if (!(g->units.cos = ft_malloc(sizeof(double) *
					(g->units.angle360 + 1))))
		return (INIT_UNITS_ERR);
	if (!(g->units.cos_div = ft_malloc(sizeof(double) *
					(g->units.angle360 + 1))))
		return (INIT_UNITS_ERR);
	if (!(g->units.tan = ft_malloc(sizeof(double) *
					(g->units.angle360 + 1))))
		return (INIT_UNITS_ERR);
	if (!(g->units.tan_div = ft_malloc(sizeof(double) *
					(g->units.angle360 + 1))))
		return (INIT_UNITS_ERR);
	return (0);
}

static int	init_steps(t_game *g)
{
	if (!(g->units.horizontal_xstep = ft_malloc(sizeof(double) *
					(g->units.angle360 + 1))))
		return (INIT_UNITS_ERR);
	if (!(g->units.vertical_ystep = ft_malloc(sizeof(double) *
					(g->units.angle360 + 1))))
		return (INIT_UNITS_ERR);
	return (0);
}

int			init_units(t_game *g)
{
	int i;

	init_angles(g);
	if (init_fish(g) == INIT_UNITS_ERR)
		return (INIT_UNITS_ERR);
	if (init_trig(g) == INIT_UNITS_ERR)
		return (INIT_UNITS_ERR);
	if (init_steps(g) == INIT_UNITS_ERR)
		return (INIT_UNITS_ERR);
	i = 0;
	while (i <= g->units.angle360)
	{
		calc_trig(g, i);
		calc_horizontal_xstep(g, i);
		calc_vertical_ystep(g, i);
		i++;
	}
	return (0);
}
