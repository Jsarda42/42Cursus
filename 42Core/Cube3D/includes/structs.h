/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:23:35 by jsarda            #+#    #+#             */
/*   Updated: 2024/08/28 09:44:04 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>

typedef struct s_image
{
	char		*img_filename;
	void		*xpm_ptr;
	int			bpp;
	int			endian;
	int			size_line;
	char		*img_data;
	int			h;
	int			w;
}				t_image;

typedef struct s_rayhit
{
	double		distance;
	char		side;
	double		hit_x;
	double		hit_y;
	int			orientation;
	double		delta_x;
	double		delta_y;
	int			map_x;
	int			map_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			step_x;
	int			step_y;
	double		side_dist_x;
	double		side_dist_y;
}				t_rayhit;

typedef struct s_map
{
	char		*map_filename;
	int			map_size;
	char		**game_map;
	char		**map_str;
}				t_map;

typedef struct s_line
{
	int			x;
	int			y;
}				t_line;

typedef struct s_graph
{
	int			wall_height;
	int			draw_start;
	int			draw_end;
	int			texture_x;
	int			texture_y;
	int			color;
	int			texture_width;
	int			texture_height;
}				t_graph;

typedef struct s_sys
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			floor_color[3];
	int			ceil_color[3];
	t_image		no_wall;
	t_image		so_wall;
	t_image		we_wall;
	t_image		ea_wall;
	t_map		map_sys;
	int			s_h;
	int			s_w;
	int			key_x;
	int			key_y;
	int			key_dir;
	int			prev_mouse_x;
	char		*img_data;
	void		*img;
	int			bpp;
	int			endian;
	int			size_line;
	int			ply_pos_y;
	int			ply_pos_x;
	float		pos_x;
	float		pos_y;
	float		dir;
	t_rayhit	rayhit;
	t_graph		graph;
}				t_sys;

#endif
