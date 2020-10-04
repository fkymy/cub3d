/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse_elem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufukuya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 23:39:30 by yufukuya          #+#    #+#             */
/*   Updated: 2020/08/09 16:56:30 by yufukuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "allocation.h"

static int	parse_resolution(char *line, t_cub *cub)
{
	line++;
	skip_spaces(&line);
	cub->res_width = ft_atoi(line);
	skip_digits(&line);
	skip_spaces(&line);
	cub->res_height = ft_atoi(line);
	return (CUB_PARSE_SUCCESS);
}

static int	parse_texture_path(char id, char *line, t_cub *cub)
{
	char *res;

	line = line + 2;
	skip_spaces(&line);
	if (!(res = ft_strdup(line)))
		return (CUB_PARSE_ERR);
	add_allocation(res);
	if (id == 'N')
		cub->no_texture = res;
	else if (id == 'S')
		cub->so_texture = res;
	else if (id == 'W')
		cub->we_texture = res;
	else if (id == 'E')
		cub->ea_texture = res;
	else if (id == 'P')
		cub->sprite_texture = res;
	else
		return (CUB_PARSE_ERR);
	return (CUB_PARSE_SUCCESS);
}

static void	set_rgb(int rgb[3], char **line)
{
	(*line)++;
	skip_spaces(line);
	rgb[0] = ft_isdigit(**line) ? ft_atoi(*line) : -1;
	skip_digits(line);
	(*line)++;
	rgb[1] = ft_isdigit(**line) ? ft_atoi(*line) : -1;
	skip_digits(line);
	(*line)++;
	rgb[2] = ft_isdigit(**line) ? ft_atoi(*line) : -1;
}

static int	parse_color(char id, char *line, t_cub *cub)
{
	int rgb[3];

	set_rgb(rgb, &line);
	if (id == 'F')
	{
		cub->floor_rgba.r = rgb[0];
		cub->floor_rgba.g = rgb[1];
		cub->floor_rgba.b = rgb[2];
		cub->floor_rgba.a = 0;
	}
	if (id == 'C')
	{
		cub->ceil_rgba.r = rgb[0];
		cub->ceil_rgba.g = rgb[1];
		cub->ceil_rgba.b = rgb[2];
		cub->ceil_rgba.a = 0;
	}
	return (CUB_PARSE_SUCCESS);
}

int			cub_parse_elem(char *line, t_cub *cub)
{
	int skip_empty_line;

	skip_empty_line = 1;
	if (ft_strncmp(line, "R ", 2) == 0)
		return (parse_resolution(line, cub));
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (parse_texture_path('N', line, cub));
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (parse_texture_path('S', line, cub));
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (parse_texture_path('W', line, cub));
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (parse_texture_path('E', line, cub));
	if (ft_strncmp(line, "S ", 2) == 0)
		return (parse_texture_path('P', line, cub));
	if (ft_strncmp(line, "F ", 2) == 0)
		return (parse_color('F', line, cub));
	if (ft_strncmp(line, "C ", 2) == 0)
		return (parse_color('C', line, cub));
	if (is_empty_line(line))
		return (skip_empty_line);
	return (CUB_PARSE_DONE);
}
