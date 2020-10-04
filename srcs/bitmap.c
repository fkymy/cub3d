/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufukuya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 23:33:40 by yufukuya          #+#    #+#             */
/*   Updated: 2020/08/09 17:57:43 by yufukuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "allocation.h"

#define BMP_HEADER_SIZE 14
#define DIB_HEADER_SIZE 40
#define BMP_BPP 4
#define BMP_NUM_PLANES 1

static void		ft_itoc(unsigned char *s, int i)
{
	s[0] = (unsigned char)(i);
	s[1] = (unsigned char)(i >> 8);
	s[2] = (unsigned char)(i >> 16);
	s[3] = (unsigned char)(i >> 24);
}

static void		write_header(int fd, t_game *g)
{
	unsigned char	header[54];
	int				filesize;

	filesize = BMP_HEADER_SIZE + DIB_HEADER_SIZE +
		(BMP_BPP * g->pp.width * g->pp.height);
	ft_memset(header, 0, 54);
	ft_memcpy(header, "BM", 2);
	ft_itoc(header + 2, filesize);
	header[10] = (unsigned char)(BMP_HEADER_SIZE + DIB_HEADER_SIZE);
	header[14] = (unsigned char)DIB_HEADER_SIZE;
	ft_itoc(header + 18, g->pp.width);
	ft_itoc(header + 22, g->pp.height);
	header[26] = (unsigned char)BMP_NUM_PLANES;
	header[28] = (unsigned int)(BMP_BPP * 8);
	write(fd, header, BMP_HEADER_SIZE + DIB_HEADER_SIZE);
}

static void		write_pixels(int fd, t_game *g)
{
	int row;
	int col;
	int row_size;
	int padding;

	row = g->pp.height - 1;
	row_size = (32 * g->pp.width / 32) * 4;
	padding = (row_size % 4) == 0 ? 0 : 4 - (row_size % 4);
	while (row >= 0)
	{
		col = 0;
		while (col < g->pp.width)
		{
			write(fd, &g->buf.data[row][col], BMP_BPP);
			write(fd, "\0\0\0", padding);
			col++;
		}
		row--;
	}
}

void			save_bitmap(char *cubname, t_game *g)
{
	char	*name;
	int		fd;

	if (!(name = ft_strjoin(cubname, ".bmp")))
		exit_free("Failed to save bitmap.\n");
	add_allocation(name);
	if ((fd = open(name, O_CREAT | O_RDWR, 0666)) == -1)
		exit_free("Failed to open bmp file\n");
	write_header(fd, g);
	write_pixels(fd, g);
	close(fd);
}
