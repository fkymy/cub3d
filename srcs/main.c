/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufukuya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 00:04:58 by yufukuya          #+#    #+#             */
/*   Updated: 2020/10/04 14:15:14 by yufukuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "game.h"
#include "allocation.h"

static int	simple_error(char *s)
{
	int len;

	len = ft_strlen(s);
	write(1, s, len);
	return (1);
}

static void	game_start(char *cubfile)
{
	t_cub	*cub;
	t_game	*g;

	if (!(cub = cub_new()))
		exit_with_message("Error initializing cub\n");
	if (!(g = game_new()))
		exit_free("Error initializing game\n");
	cub_parse(cubfile, cub);
	if (!(g->mlx = mlx_init()))
		exit_free("Error initializing mlx\n");
	init_game(g, cub);
	g->win = mlx_new_window(g->mlx,
			g->pp.width, g->pp.height, "cat on the shore");
	g->img.img = mlx_new_image(g->mlx, g->pp.width, g->pp.height);
	g->img.data = (int *)mlx_get_data_addr(g->img.img,
			&g->img.bpp, &g->img.size_l, &g->img.endian);
	mlx_loop_hook(g->mlx, &game_loop, g);
	mlx_hook(g->win, 2, 1L << 0, &event_key_press, g);
	mlx_hook(g->win, 17, 1L << 17, &event_destroy_notify, g);
	mlx_loop(g->mlx);
	free(g->mlx);
	ft_lstclear(&g_allocations, free);
	exit(0);
}

static void	game_capture(char *cubfile)
{
	t_cub	*cub;
	t_game	*g;

	if (!(cub = cub_new()))
		exit_with_message("Error initializing cub\n");
	if (!(g = game_new()))
		exit_free("Error initializing g\n");
	cub_parse(cubfile, cub);
	if (!(g->mlx = mlx_init()))
		exit_free("Error initializing mlx\n");
	init_game(g, cub);
	cast_rays(g);
	/* cast_sprites(g); */
	save_bitmap("海辺に猫", g);
	free(g->mlx);
	ft_lstclear(&g_allocations, free);
	exit(0);
}

int			main(int argc, char *argv[])
{
	if (argc < 2 || argc > 3)
		return (simple_error("Invalid arguments.\n"));
	if (!ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
		return (simple_error(".cub file must be specified.\n"));
	if (argc == 3 && ft_strncmp(argv[2], "--save", ft_strlen(argv[2])) != 0)
		return (simple_error("Invalid option. Options: --save\n"));
	if (argc == 2)
		game_start(argv[1]);
	else
		game_capture(argv[1]);
	return (0);
}
