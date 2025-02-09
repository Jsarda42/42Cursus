/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edegraev <edegraev@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:23:54 by jsarda            #+#    #+#             */
/*   Updated: 2024/08/28 09:40:06 by edegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx_linux/mlx.h"
# include "structs.h"
# include <../mlx_linux/mlx_int.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>

# define FOV 50.0
# define M_PI 3.14159265358979323846
# define MOVE_SPEED 0.02
# define ROTATE_SPEED 1
# define STEP_RENDER 0.01
# define COLLISION_MARGIN 0.1

// src
int		close_game(t_sys *sys);
int		handle_keypress_up(int keysym, t_sys *sys);
int		handle_keypress_down(int keysym, t_sys *sys);
int		update_screen(void *data);
void	move_player(t_sys *sys);
void	draw_vertical_line(t_sys *sys, int x);
void	get_texture_dimensions(t_sys *sys, int *texture_w, int *texture_h);
void	set_wall_h(t_sys *sys, int *wall_h, int *draw_start, int *draw_end);
void	draw_ceiling(t_sys *sys, int x, int draw_start);
int		get_texture_x(t_sys *sys, int texture_width);
void	set_texture_y(t_sys *sys, int y);
void	put_pixel_to_buffer(t_sys *sys, int x, int y, int color);
void	draw_floor(t_sys *sys, int x, int draw_end);
void	distance_raycasting(t_sys *sys, double angle);
void	set_side(t_sys *sys, char orientation);
int		rgb_to_hex(int r, int g, int b);
double	fix_angle(double angle);
int		get_texture_x(t_sys *sys, int texture_width);

// init
void	init_data(t_sys *sys, char **argv);
void	init_map(t_sys *sys);
void	init_window(t_sys *sys);
void	init_textures(t_sys *sys);

// parse
void	parse_map(t_sys *sys);
int		parse_identifier(t_sys *sys, char **map);
void	parse_map_grid(t_sys *sys);
void	parse_cardinals(t_sys *sys, char *cardinal_line);
void	parse_colors(t_sys *sys, char *colors_line, char c);
int		valid_rgb(char *colors_line, int *i);
int		is_player_position(char c);
void	process_player_position(t_sys *sys, int row, int col,
			int *player_number);

// utils
int		ft_count_args(char **arg);
void	ft_errors(t_sys *sys, char *message, int error_status);
void	free_all(t_sys *sys);
void	check_args_nbr(t_sys *sys, char **str, int nbr);
void	mid_valid_char(t_sys *sys, char c);
void	ext_valid_char(t_sys *sys, char c);
int		is_identifier(char identifier);

#endif
