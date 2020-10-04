/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufukuya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 23:44:37 by yufukuya          #+#    #+#             */
/*   Updated: 2020/08/09 18:14:16 by yufukuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "cub.h"
#include "allocation.h"

int			init_texture(t_game *g, t_cub *cub)
{
	if (!(g->buf.textures = (int **)ft_malloc(sizeof(int *) * 5)))
		return (INIT_TEXTURE_ERR);
	if (load_texture(g, cub->no_texture, NO_TEXTURE) == INIT_TEXTURE_ERR)
		return (INIT_TEXTURE_ERR);
	if (load_texture(g, cub->so_texture, SO_TEXTURE) == INIT_TEXTURE_ERR)
		return (INIT_TEXTURE_ERR);
	if (load_texture(g, cub->we_texture, WE_TEXTURE) == INIT_TEXTURE_ERR)
		return (INIT_TEXTURE_ERR);
	if (load_texture(g, cub->ea_texture, EA_TEXTURE) == INIT_TEXTURE_ERR)
		return (INIT_TEXTURE_ERR);
	if (load_texture(g, cub->sprite_texture, S_TEXTURE) == INIT_TEXTURE_ERR)
		return (INIT_TEXTURE_ERR);
	return (0);
}
