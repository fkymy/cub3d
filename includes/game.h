/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufukuya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 17:35:46 by yufukuya          #+#    #+#             */
/*   Updated: 2020/10/04 14:12:01 by yufukuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <math.h>
# include <fcntl.h>
# include "keys.h"
# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include "cub.h"

# define NO_TEXTURE 0
# define SO_TEXTURE 1
# define WE_TEXTURE 2
# define EA_TEXTURE 3
# define S_TEXTURE 4

# define INIT_UNITS_ERR 1
# define INIT_PLAYER_ERR 2
# define INIT_BUF_ERR 4
# define INIT_TEXTURE_ERR 8
# define INIT_SPRITES_ERR 16

typedef struct	s_units
{
	int			angle60;
	int			angle30;
	int			angle15;
	int			angle90;
	int			angle180;
	int			angle270;
	int			angle360;
	int			angle0;
	int			angle5;
	int			angle10;
	int			angle45;
	int			angle1;
	double		*sin;
	double		*sin_div;
	double		*cos;
	double		*cos_div;
	double		*tan;
	double		*tan_div;
	double		*fish;
	double		*horizontal_xstep;
	double		*vertical_ystep;
}				t_units;

typedef struct	s_player
{
	int			x;
	int			y;
	int			arc;
	int			dist_to_pp;
	int			height;
	int			speed;
}				t_player;

typedef struct	s_pp
{
	int			width;
	int			height;
	int			y_center;
}				t_pp;

typedef struct	s_grid
{
	int			height;
	int			width;
	char		**map;
}				t_grid;

typedef struct	s_buf
{
	int			**data;
	int			**textures;
	int			tex_width[5];
	int			tex_height[5];
	int			tex_size[5];
}				t_buf;

typedef struct	s_img
{
	void		*img;
	int			*data;
	int			bpp;
	int			size_l;
	int			endian;
}				t_img;

typedef struct	s_sprite
{
	int			x;
	int			y;
	int			visible;
	double		distance;
	double		angle;
	double		angle_diff;
	int			arc_diff;
	double		proj_height;
	double		proj_width;
	int			xcenter;
	int			xstart;
	int			xend;
	int			ystart;
	int			yend;
}				t_sprite;

typedef struct	s_game
{
	void		*mlx;
	void		*win;
	int			tile_size;
	int			wall_height;
	int			floor_color;
	int			ceil_color;
	t_img		img;
	t_buf		buf;
	t_units		units;
	t_grid		grid;
	t_player	player;
	t_pp		pp;
	t_sprite	*sprites;
	int			num_sprites;
	int			*sprite_order;
	double		*zbuffer;
}				t_game;

typedef struct	s_ray
{
	int			cast_arc;
	int			cast_column;
	int			vertical_grid;
	int			horizontal_grid;
	double		dist_to_next_vertical_grid;
	double		dist_to_next_horizontal_grid;
	double		x_intersection;
	double		y_intersection;
	double		dist_to_next_x_intersection;
	double		dist_to_next_y_intersection;
	int			x_grid_index;
	int			y_grid_index;
	double		dist_to_vertical_grid_being_hit;
	double		dist_to_horizontal_grid_being_hit;
	double		distance;
	double		proj_wall_height;
	char		wall_side;
	double		x_offset;
	int			top_of_wall;
	int			bottom_of_wall;
	double		step;
}				t_ray;

void			exit_with_message(char *s);
void			exit_free(char *s);

void			init_game(t_game *g, t_cub *cub);

t_game			*game_new(void);

int				game_loop(t_game *g);
void			cast_rays(t_game *g);

void			find_first_x_intersection(t_game *g, t_ray *ray);
void			find_horizontal_wall(t_game *g, t_ray *ray);
void			set_for_horizonta_wall(t_game *g, t_ray *ray);
void			find_first_y_intersection(t_game *g, t_ray *ray);
void			find_vertical_wall(t_game *g, t_ray *ray);
void			set_for_vertical_wall(t_game *g, t_ray *ray);
void			render_background_to_buffer(t_game *g, t_ray *ray);
void			render_wall_to_buffer(t_game *g, t_ray *ray);
// void			cast_sprites(t_game *g);
// void			brutally_calculate_xcenter(t_game *g, int i);
// void			sort_sprites(t_game *g);

int				init_units(t_game *g);
void			calc_trig(t_game *g, int i);
void			calc_horizontal_xstep(t_game *g, int i);
void			calc_vertical_ystep(t_game *g, int i);
int				init_texture(t_game *g, t_cub *cub);
int				load_texture(t_game *g, char *path, int index);
int				init_sprites(t_game *g, t_cub *cub);

double			arc_to_rad(t_game *g, int arc_angle);
int				rad_to_arc(t_game *g, double rad);
int				map_has_wall_at(t_game *g, double x, double y);

double			distance_between_points(int x1, int x2, int y1, int y2);

int				event_destroy_notify(t_game *g);
int				event_key_press(int key, t_game *g);

int				rotate_player(int key, t_game *g);
int				move_player_forward(t_game *g);
int				move_player_backward(t_game *g);
int				move_player_right(t_game *g);
int				move_player_left(t_game *g);

void			save_bitmap(char *cubname, t_game *g);

#endif
