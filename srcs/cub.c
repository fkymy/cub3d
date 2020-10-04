/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufukuya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 23:38:29 by yufukuya          #+#    #+#             */
/*   Updated: 2020/08/09 16:55:41 by yufukuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "allocation.h"

t_cub	*cub_new(void)
{
	t_cub *cub;

	cub = (t_cub *)ft_malloc(sizeof(t_cub));
	if (!cub)
		return (NULL);
	cub->fd = -1;
	cub->res_width = 0;
	cub->res_height = 0;
	cub->no_texture = 0;
	cub->so_texture = 0;
	cub->we_texture = 0;
	cub->ea_texture = 0;
	cub->sprite_texture = 0;
	cub->map = 0;
	cub->map_width = 0;
	cub->map_height = 0;
	cub->start_row = 0;
	cub->start_col = 0;
	cub->start_dir = 0;
	return (cub);
}
