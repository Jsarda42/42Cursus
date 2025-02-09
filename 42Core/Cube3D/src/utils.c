/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edegraev <edegraev@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 09:37:43 by edegraev          #+#    #+#             */
/*   Updated: 2024/08/28 09:38:48 by edegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_side(t_sys *sys, char orientation)
{
	if (orientation == 'x')
	{
		if (sys->rayhit.step_x > 0)
			sys->rayhit.side = 'E';
		else
			sys->rayhit.side = 'W';
	}
	else
	{
		if (sys->rayhit.step_y > 0)
			sys->rayhit.side = 'S';
		else
			sys->rayhit.side = 'N';
	}
}

int	rgb_to_hex(int r, int g, int b)
{
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	if (r < 0)
		r = 0;
	if (g < 0)
		g = 0;
	if (b < 0)
		b = 0;
	return ((r << 16) | (g << 8) | b);
}

void	set_texture_y(t_sys *sys, int y)
{
	int	d;

	d = y * 256 - sys->s_h * 128 + sys->graph.wall_height * 128;
	sys->graph.texture_y = ((d * sys->graph.texture_height)
			/ sys->graph.wall_height) / 256;
	if (sys->graph.texture_y < 0)
		sys->graph.texture_y = 0;
	if (sys->graph.texture_y >= sys->graph.texture_height)
		sys->graph.texture_y = sys->graph.texture_height - 1;
}

double	fix_angle(double angle)
{
	if (angle < 0)
		angle += 360;
	else if (angle >= 360)
		angle -= 360;
	return (angle);
}

void	get_texture_dimensions(t_sys *sys, int *texture_w, int *texture_h)
{
	if (sys->rayhit.side == 'N')
	{
		*texture_w = sys->no_wall.w;
		*texture_h = sys->no_wall.h;
	}
	else if (sys->rayhit.side == 'S')
	{
		*texture_w = sys->so_wall.w;
		*texture_h = sys->so_wall.h;
	}
	else if (sys->rayhit.side == 'E')
	{
		*texture_w = sys->ea_wall.w;
		*texture_h = sys->ea_wall.h;
	}
	else if (sys->rayhit.side == 'W')
	{
		*texture_w = sys->we_wall.w;
		*texture_h = sys->we_wall.h;
	}
}
