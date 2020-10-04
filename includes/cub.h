/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufukuya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 17:33:38 by yufukuya          #+#    #+#             */
/*   Updated: 2020/08/09 17:45:12 by yufukuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include "../libft/libft.h"

# define CUB_PARSE_SUCCESS 1
# define CUB_PARSE_ERR -1
# define CUB_PARSE_DONE 0

# define CUB_VALID 1
# define CUB_INVALID -1

typedef struct	s_rgba
{
	int			r;
	int			g;
	int			b;
	int			a;
}				t_rgba;

typedef struct	s_cub
{
	int			fd;
	int			res_width;
	int			res_height;
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	char		*sprite_texture;
	t_rgba		floor_rgba;
	t_rgba		ceil_rgba;
	char		**map;
	int			map_width;
	int			map_height;
	int			start_row;
	int			start_col;
	char		start_dir;
}				t_cub;

t_cub			*cub_new(void);
void			cub_clear(t_cub **cub);

void			cub_parse(char *cubfile, t_cub *cub);

int				cub_parse_elem(char *line, t_cub *cub);
int				cub_parse_map(char *line, t_cub *cub);

int				get_largest_width(char **map);
int				get_starting_point(char **map, int *a, int *b);

int				ft_isspace(int c);
void			skip_spaces(char **line);
void			skip_digits(char **line);
int				is_empty_line(char *line);
char			*ft_strjoin_delim(char *s1, char delim, char *s2);
char			*ft_strjoin_delim_free(char *s1, char delim, char *s2);

int				cub_validate(t_cub *cub);
int				check_has_only_valid_chr(t_cub *cub);
int				search_hole(t_cub *cub);

#endif
