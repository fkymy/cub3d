/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufukuya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 23:42:32 by yufukuya          #+#    #+#             */
/*   Updated: 2020/08/09 17:57:28 by yufukuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "allocation.h"

static int	close_game(t_game *g)
{
	if (g->mlx && g->win)
		mlx_destroy_window(g->mlx, g->win);
	if (g->mlx && g->img.img)
		mlx_destroy_image(g->mlx, g->img.img);
	free(g->mlx);
	ft_lstclear(&g_allocations, free);
	exit(0);
	return (0);
}

int			event_destroy_notify(t_game *g)
{
	return (close_game(g));
}

int			event_key_press(int key, t_game *g)
{
	if (key == KEY_LEFT)
		return (rotate_player(KEY_LEFT, g));
	if (key == KEY_RIGHT)
		return (rotate_player(KEY_RIGHT, g));
	if (key == KEY_W)
		return (move_player_forward(g));
	if (key == KEY_S)
		return (move_player_backward(g));
	if (key == KEY_D)
		return (move_player_right(g));
	if (key == KEY_A)
		return (move_player_left(g));
	if (key == KEY_ESC)
		return (close_game(g));
	return (0);
}
