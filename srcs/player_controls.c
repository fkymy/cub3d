/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufukuya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 23:47:06 by yufukuya          #+#    #+#             */
/*   Updated: 2020/08/07 23:47:56 by yufukuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	rotate_player(int key, t_game *g)
{
	if (key == KEY_LEFT)
	{
		g->player.arc -= g->units.angle5;
		if (g->player.arc < g->units.angle0)
			g->player.arc += g->units.angle360;
	}
	if (key == KEY_RIGHT)
	{
		g->player.arc += g->units.angle5;
		if (g->player.arc >= g->units.angle360)
			g->player.arc -= g->units.angle360;
	}
	return (0);
}

int	move_player_forward(t_game *g)
{
	double player_xdir;
	double player_ydir;
	double new_player_x;
	double new_player_y;

	player_xdir = g->units.cos[g->player.arc];
	player_ydir = g->units.sin[g->player.arc];
	new_player_x = 0;
	new_player_y = 0;
	new_player_x = g->player.x + round(player_xdir * g->player.speed);
	new_player_y = g->player.y + round(player_ydir * g->player.speed);
	if (!map_has_wall_at(g, new_player_x, new_player_y))
	{
		g->player.x = new_player_x;
		g->player.y = new_player_y;
	}
	return (0);
}

int	move_player_backward(t_game *g)
{
	double player_xdir;
	double player_ydir;
	double new_player_x;
	double new_player_y;

	player_xdir = g->units.cos[g->player.arc];
	player_ydir = g->units.sin[g->player.arc];
	new_player_x = 0;
	new_player_y = 0;
	new_player_x = g->player.x - round(player_xdir * g->player.speed);
	new_player_y = g->player.y - round(player_ydir * g->player.speed);
	if (!map_has_wall_at(g, new_player_x, new_player_y))
	{
		g->player.x = new_player_x;
		g->player.y = new_player_y;
	}
	return (0);
}

int	move_player_right(t_game *g)
{
	double	player_xdir;
	double	player_ydir;
	double	new_player_x;
	double	new_player_y;
	int		right_arc;

	right_arc = g->player.arc + g->units.angle90;
	if (right_arc > g->units.angle360)
		right_arc = right_arc - g->units.angle360;
	player_xdir = g->units.cos[right_arc];
	player_ydir = g->units.sin[right_arc];
	new_player_x = g->player.x + round(player_xdir * g->player.speed);
	new_player_y = g->player.y + round(player_ydir * g->player.speed);
	if (!map_has_wall_at(g, new_player_x, new_player_y))
	{
		g->player.x = new_player_x;
		g->player.y = new_player_y;
	}
	return (0);
}

int	move_player_left(t_game *g)
{
	double	player_xdir;
	double	player_ydir;
	double	new_player_x;
	double	new_player_y;
	int		right_arc;

	right_arc = g->player.arc + g->units.angle90;
	if (right_arc > g->units.angle360)
		right_arc = right_arc - g->units.angle360;
	player_xdir = g->units.cos[right_arc];
	player_ydir = g->units.sin[right_arc];
	new_player_x = g->player.x - round(player_xdir * g->player.speed);
	new_player_y = g->player.y - round(player_ydir * g->player.speed);
	if (!map_has_wall_at(g, new_player_x, new_player_y))
	{
		g->player.x = new_player_x;
		g->player.y = new_player_y;
	}
	return (0);
}
