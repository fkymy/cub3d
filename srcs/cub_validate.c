/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufukuya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 23:41:08 by yufukuya          #+#    #+#             */
/*   Updated: 2020/08/07 23:41:30 by yufukuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	validate_texture_paths(t_cub *cub)
{
	if (cub->no_texture == NULL)
		return (CUB_INVALID);
	if (cub->so_texture == NULL)
		return (CUB_INVALID);
	if (cub->we_texture == NULL)
		return (CUB_INVALID);
	if (cub->ea_texture == NULL)
		return (CUB_INVALID);
	if (cub->sprite_texture == NULL)
		return (CUB_INVALID);
	return (CUB_VALID);
}

static int	validate_resolution(t_cub *cub)
{
	if (cub->res_width <= 0)
		return (CUB_INVALID);
	if (cub->res_height <= 0)
		return (CUB_INVALID);
	return (CUB_VALID);
}

static int	validate_colors(t_cub *cub)
{
	if (cub->floor_rgba.r < 0 || cub->floor_rgba.r > 255)
		return (CUB_INVALID);
	if (cub->floor_rgba.g < 0 || cub->floor_rgba.g > 255)
		return (CUB_INVALID);
	if (cub->floor_rgba.b < 0 || cub->floor_rgba.b > 255)
		return (CUB_INVALID);
	if (cub->ceil_rgba.r < 0 || cub->ceil_rgba.r > 255)
		return (CUB_INVALID);
	if (cub->ceil_rgba.g < 0 || cub->ceil_rgba.g > 255)
		return (CUB_INVALID);
	if (cub->ceil_rgba.b < 0 || cub->ceil_rgba.b > 255)
		return (CUB_INVALID);
	return (CUB_VALID);
}

static int	validate_map(t_cub *cub)
{
	if (cub->map_width <= 0 || cub->map_height <= 0)
		return (CUB_INVALID);
	if (!check_has_only_valid_chr(cub))
		return (CUB_INVALID);
	if (search_hole(cub))
		return (CUB_INVALID);
	return (CUB_VALID);
}

int			cub_validate(t_cub *cub)
{
	if (validate_texture_paths(cub) == CUB_INVALID)
		return (CUB_INVALID);
	if (validate_resolution(cub) == CUB_INVALID)
		return (CUB_INVALID);
	if (validate_colors(cub) == CUB_INVALID)
		return (CUB_INVALID);
	if (validate_map(cub) == CUB_INVALID)
		return (CUB_INVALID);
	return (CUB_VALID);
}
