/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufukuya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 23:40:03 by yufukuya          #+#    #+#             */
/*   Updated: 2020/08/09 16:57:25 by yufukuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "get_next_line.h"
#include "allocation.h"

static void	align_width_height(t_cub *cub, char **map)
{
	int w;
	int h;

	w = get_largest_width(map);
	h = 0;
	while (map[h])
		h++;
	cub->map_width = w;
	cub->map_height = h;
}

static int	set_aligned_map(t_cub *cub, char **map)
{
	char	*tmp;
	int		i;

	align_width_height(cub, map);
	i = 0;
	while (map[i])
	{
		if (!(tmp = (char *)malloc(sizeof(char) * (cub->map_width + 1))))
			return (CUB_PARSE_ERR);
		ft_memset(tmp, ' ', cub->map_width);
		tmp[cub->map_width] = '\0';
		ft_memcpy(tmp, map[i], ft_strlen(map[i]));
		free(map[i]);
		map[i] = tmp;
		add_allocation(map[i]);
		i++;
	}
	cub->map = map;
	return (CUB_PARSE_SUCCESS);
}

char		*parse_raw_map(char *line, t_cub *cub)
{
	char	*raw;
	int		ret;

	if (!(raw = ft_strdup(line)))
		return (NULL);
	free(line);
	while ((ret = get_next_line(cub->fd, &line)) > 0)
	{
		raw = ft_strjoin_delim_free(raw, '\n', line);
		free(line);
	}
	if (ret == -1)
	{
		free(raw);
		return (NULL);
	}
	raw = ft_strjoin_delim_free(raw, '\n', line);
	free(line);
	return (raw);
}

int			cub_parse_map(char *line, t_cub *cub)
{
	char	*raw;
	char	**map;

	raw = parse_raw_map(line, cub);
	map = ft_split(raw, '\n');
	free(raw);
	if (map == NULL)
		return (CUB_PARSE_ERR);
	add_allocation(map);
	if (set_aligned_map(cub, map) == CUB_PARSE_ERR)
		return (CUB_PARSE_ERR);
	if (!get_starting_point(map, &cub->start_row, &cub->start_col))
		return (CUB_PARSE_ERR);
	cub->start_dir = map[cub->start_row][cub->start_col];
	return (CUB_PARSE_DONE);
}
