/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufukuya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 23:39:12 by yufukuya          #+#    #+#             */
/*   Updated: 2020/08/07 23:39:24 by yufukuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "get_next_line.h"
#include "allocation.h"

void	exit_cub_parse(t_cub *cub, char *message)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(message, 1);
	close(cub->fd);
	ft_lstclear(&g_allocations, free);
	exit(1);
}

void	cub_parse(char *cubfile, t_cub *cub)
{
	char	*line;
	int		ret;

	if ((cub->fd = open(cubfile, O_RDONLY)) == -1)
		exit_cub_parse(cub, "Error opening cubfile.\n");
	while (get_next_line(cub->fd, &line) > 0)
	{
		if ((ret = cub_parse_elem(line, cub)) == CUB_PARSE_ERR)
		{
			free(line);
			exit_cub_parse(cub, "Could not parse elements.\n");
		}
		if (ret == CUB_PARSE_DONE)
			break ;
		free(line);
	}
	if (cub_parse_map(line, cub) == CUB_PARSE_ERR)
		exit_cub_parse(cub, "Could not parse map.\n");
	if (cub_validate(cub) == CUB_INVALID)
		exit_cub_parse(cub, "Cubfile is invalid\n");
	close(cub->fd);
}
