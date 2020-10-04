/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_validate_map_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufukuya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 16:54:42 by yufukuya          #+#    #+#             */
/*   Updated: 2020/08/09 16:54:50 by yufukuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_has_only_valid_chr(t_cub *cub)
{
	int had_start;
	int i;
	int j;

	had_start = 0;
	i = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (!ft_strchr(" 012NSWE", cub->map[i][j]))
				return (0);
			if (cub->map[i][j] > '2' && had_start)
				return (0);
			if (cub->map[i][j] > '2')
				had_start = 1;
			j++;
		}
		i++;
	}
	return (had_start ? 1 : 0);
}
