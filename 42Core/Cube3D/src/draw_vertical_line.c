/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vertical_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edegraev <edegraev@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 09:24:53 by edegraev          #+#    #+#             */
/*   Updated: 2024/08/28 09:29:19 by edegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_vertical_line_n(t_sys *sys)
{
	if (sys->rayhit.side != 'N')
		return ;
	sys->graph.texture_x = (int)(sys->rayhit.hit_x * sys->graph.texture_width)
		% sys->graph.texture_width;
	if (sys->graph.texture_x < 0)
		sys->graph.texture_x += sys->graph.texture_width;
	sys->graph.color = *(int *)(sys->no_wall.img_data + (sys->graph.texture_y
				* sys->no_wall.size_line + sys->graph.texture_x
				* (sys->no_wall.bpp / 8)));
}

static void	draw_vertical_line_s(t_sys *sys)
{
	if (sys->rayhit.side != 'S')
		return ;
	sys->graph.texture_x = (int)(sys->rayhit.hit_x * sys->graph.texture_width)
		% sys->graph.texture_width;
	if (sys->graph.texture_x < 0)
		sys->graph.texture_x += sys->graph.texture_width;
	sys->graph.texture_x = sys->graph.texture_width - sys->graph.texture_x - 1;
	sys->graph.color = *(int *)(sys->so_wall.img_data + (sys->graph.texture_y
				* sys->so_wall.size_line + sys->graph.texture_x
				* (sys->so_wall.bpp / 8)));
}

static void	draw_vertical_line_e(t_sys *sys)
{
	if (sys->rayhit.side != 'E')
		return ;
	sys->graph.texture_x = (int)(sys->rayhit.hit_y * sys->graph.texture_width)
		% sys->graph.texture_width;
	if (sys->graph.texture_x < 0)
		sys->graph.texture_x += sys->graph.texture_width;
	sys->graph.color = *(int *)(sys->ea_wall.img_data + (sys->graph.texture_y
				* sys->ea_wall.size_line + sys->graph.texture_x
				* (sys->ea_wall.bpp / 8)));
}

static void	draw_vertical_line_w(t_sys *sys)
{
	if (sys->rayhit.side != 'W')
		return ;
	sys->graph.texture_x = (int)(sys->rayhit.hit_y * sys->graph.texture_width)
		% sys->graph.texture_width;
	if (sys->graph.texture_x < 0)
		sys->graph.texture_x += sys->graph.texture_width;
	sys->graph.texture_x = sys->graph.texture_width - sys->graph.texture_x - 1;
	sys->graph.color = *(int *)(sys->we_wall.img_data + (sys->graph.texture_y
				* sys->we_wall.size_line + sys->graph.texture_x
				* (sys->we_wall.bpp / 8)));
}

void	draw_vertical_line(t_sys *sys, int x)
{
	int	y;

	get_texture_dimensions(sys, &sys->graph.texture_width,
		&sys->graph.texture_height);
	set_wall_h(sys, &sys->graph.wall_height, &sys->graph.draw_start,
		&sys->graph.draw_end);
	sys->graph.texture_x = get_texture_x(sys, sys->graph.texture_width);
	draw_ceiling(sys, x, sys->graph.draw_start);
	y = sys->graph.draw_start;
	while (y < sys->graph.draw_end)
	{
		set_texture_y(sys, y);
		draw_vertical_line_n(sys);
		draw_vertical_line_s(sys);
		draw_vertical_line_e(sys);
		draw_vertical_line_w(sys);
		put_pixel_to_buffer(sys, x, y, sys->graph.color);
		y++;
	}
	draw_floor(sys, x, sys->graph.draw_end);
}
