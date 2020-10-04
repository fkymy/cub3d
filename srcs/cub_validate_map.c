/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_validate_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufukuya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 23:41:35 by yufukuya          #+#    #+#             */
/*   Updated: 2020/08/09 17:05:42 by yufukuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	fill_map(t_cub *cub, int row, int col)
{
	if (row < 0 || col < 0 ||
		row >= cub->map_height || col >= cub->map_width)
		return ;
	if (cub->map[row][col] == '1' || cub->map[row][col] & 4)
		return ;
	if (!(cub->map[row][col] == '0' || cub->map[row][col] == '2'))
		return ;
	cub->map[row][col] |= 4;
	fill_map(cub, row + 1, col);
	fill_map(cub, row - 1, col);
	fill_map(cub, row, col + 1);
	fill_map(cub, row, col - 1);
}

static int	check_has_hole(t_cub *cub, int row, int col)
{
	if (row - 1 < 0 || col - 1 < 0 ||
		row + 1 >= cub->map_height || col + 1 >= cub->map_width)
		return (1);
	if (cub->map[row + 1][col] == ' ')
		return (1);
	if (cub->map[row - 1][col] == ' ')
		return (1);
	if (cub->map[row][col + 1] == ' ')
		return (1);
	if (cub->map[row][col - 1] == ' ')
		return (1);
	return (0);
}

static int	check_has_hole_and_unfill(t_cub *cub)
{
	int has_hole;
	int i;
	int j;

	has_hole = 0;
	i = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (cub->map[i][j] & 4)
			{
				if (check_has_hole(cub, i, j) == 1)
					has_hole = 1;
				cub->map[i][j] &= ~4;
			}
			j++;
		}
		i++;
	}
	return (has_hole);
}

int			search_hole(t_cub *cub)
{
	int has_hole;

	has_hole = 0;
	cub->map[cub->start_row][cub->start_col] = '0';
	fill_map(cub, cub->start_row, cub->start_col);
	has_hole = check_has_hole_and_unfill(cub);
	cub->map[cub->start_row][cub->start_col] = 'N';
	return (has_hole);
}
