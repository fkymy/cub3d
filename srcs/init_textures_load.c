/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures_load.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufukuya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 18:11:40 by yufukuya          #+#    #+#             */
/*   Updated: 2020/08/09 18:12:30 by yufukuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "cub.h"
#include "allocation.h"

static void	set_tex_size(t_game *g, int w, int h, int i)
{
	g->buf.tex_size[i] = w * h;
	g->buf.tex_width[i] = w;
	g->buf.tex_height[i] = h;
}

static int	load_xpm(t_game *g, char *path, int index)
{
	t_img	t;
	int		width;
	int		height;
	int		y;
	int		x;

	t.img = mlx_xpm_file_to_image(g->mlx, path, &width, &height);
	if (t.img == NULL)
		return (INIT_TEXTURE_ERR);
	t.data = (int *)mlx_get_data_addr(t.img, &t.bpp, &t.size_l, &t.endian);
	if (!(g->buf.textures[index] = ft_malloc(sizeof(int) * (width * height))))
		return (INIT_TEXTURE_ERR);
	ft_bzero(g->buf.textures[index], width * height);
	y = -1;
	while (++y < height)
	{
		x = -1;
		while (++x < width)
			g->buf.textures[index][width * y + x] = t.data[width * y + x];
	}
	set_tex_size(g, width, height, index);
	mlx_destroy_image(g->mlx, t.img);
	return (0);
}

#if defined(__APPLE__)

static int	load_png(t_game *g, char *path, int index)
{
	t_img	t;
	int		width;
	int		height;
	int		y;
	int		x;

	t.img = mlx_png_file_to_image(g->mlx, path, &width, &height);
	if (t.img == NULL)
		return (INIT_TEXTURE_ERR);
	t.data = (int *)mlx_get_data_addr(t.img, &t.bpp, &t.size_l, &t.endian);
	if (!(g->buf.textures[index] = ft_malloc(sizeof(int) * (width * height))))
		return (INIT_TEXTURE_ERR);
	ft_bzero(g->buf.textures[index], width * height);
	y = -1;
	while (++y < height)
	{
		x = -1;
		while (++x < width)
			g->buf.textures[index][width * y + x] = t.data[width * y + x];
	}
	set_tex_size(g, width, height, index);
	mlx_destroy_image(g->mlx, t.img);
	return (0);
}

#else

static int	load_png(t_game *g, char *path, int index)
{
	(void)g;
	(void)path;
	(void)index;
	return (INIT_TEXTURE_ERR);
}

#endif

int			load_texture(t_game *g, char *path, int index)
{
	char *dot;

	dot = ft_strrchr(path, '.');
	if (!dot || dot == path)
		return (INIT_TEXTURE_ERR);
	if (ft_strncmp(dot, ".xpm", 4) == 0)
		return (load_xpm(g, path, index));
	else if (ft_strncmp(dot, ".png", 4) == 0)
		return (load_png(g, path, index));
	else
		return (INIT_TEXTURE_ERR);
}
