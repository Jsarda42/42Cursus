/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edegraev <edegraev@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:53:24 by achevron          #+#    #+#             */
/*   Updated: 2024/08/28 09:39:22 by edegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel_to_buffer(t_sys *sys, int x, int y, int color)
{
	int	offset;

	offset = (y * sys->size_line) + (x * (sys->bpp / 8));
	*(int *)(sys->img_data + offset) = color;
}

void	set_wall_h(t_sys *sys, int *wall_h, int *draw_start, int *draw_end)
{
	*wall_h = (int)(sys->s_h / sys->rayhit.distance);
	*draw_start = -*wall_h / 2 + sys->s_h / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	*draw_end = *wall_h / 2 + sys->s_h / 2;
	if (*draw_end >= sys->s_h)
		*draw_end = sys->s_h - 1;
}

void	draw_ceiling(t_sys *sys, int x, int draw_start)
{
	int	y;

	y = 0;
	while (y < draw_start)
	{
		put_pixel_to_buffer(sys, x, y, rgb_to_hex(sys->ceil_color[0],
				sys->ceil_color[1], sys->ceil_color[2]));
		y++;
	}
}

void	draw_floor(t_sys *sys, int x, int draw_end)
{
	int	y;

	y = draw_end;
	while (y < sys->s_h)
	{
		put_pixel_to_buffer(sys, x, y, rgb_to_hex(sys->floor_color[0],
				sys->floor_color[1], sys->floor_color[2]));
		y++;
	}
}

int	update_screen(void *data)
{
	t_sys	*sys;
	double	pixels_per_degree;
	int		i;
	double	angle;

	sys = (t_sys *)data;
	move_player(sys);
	pixels_per_degree = (double)(sys->s_w / FOV);
	i = 0;
	while (i < sys->s_w)
	{
		angle = (i / pixels_per_degree) - ((double)FOV / 2) + (double)sys->dir;
		angle = fix_angle(angle);
		distance_raycasting(sys, angle);
		draw_vertical_line(sys, i);
		i++;
	}
	mlx_put_image_to_window(sys->mlx_ptr, sys->win_ptr, sys->img, 0, 0);
	return (0);
}
