/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edegraev <edegraev@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 09:34:27 by edegraev          #+#    #+#             */
/*   Updated: 2024/08/28 09:36:03 by edegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_raycasting(t_sys *sys, double angle)
{
	sys->rayhit.distance = 0;
	sys->rayhit.orientation = 0;
	sys->rayhit.hit_x = sys->pos_x;
	sys->rayhit.hit_y = sys->pos_y;
	sys->rayhit.map_x = (int)sys->rayhit.hit_x;
	sys->rayhit.map_y = (int)sys->rayhit.hit_y;
	sys->rayhit.delta_x = cos(angle);
	sys->rayhit.delta_y = sin(angle);
	sys->rayhit.delta_dist_x = fabs(1 / sys->rayhit.delta_x);
	sys->rayhit.delta_dist_y = fabs(1 / sys->rayhit.delta_y);
}

static void	step_side_distance(t_sys *sys)
{
	if (sys->rayhit.delta_x < 0)
	{
		sys->rayhit.step_x = -1;
		sys->rayhit.side_dist_x = (sys->rayhit.hit_x - sys->rayhit.map_x)
			* sys->rayhit.delta_dist_x;
	}
	else
	{
		sys->rayhit.step_x = 1;
		sys->rayhit.side_dist_x = (sys->rayhit.map_x + 1.0 - sys->rayhit.hit_x)
			* sys->rayhit.delta_dist_x;
	}
	if (sys->rayhit.delta_y < 0)
	{
		sys->rayhit.step_y = -1;
		sys->rayhit.side_dist_y = (sys->rayhit.hit_y - sys->rayhit.map_y)
			* sys->rayhit.delta_dist_y;
	}
	else
	{
		sys->rayhit.step_y = 1;
		sys->rayhit.side_dist_y = (sys->rayhit.map_y + 1.0 - sys->rayhit.hit_y)
			* sys->rayhit.delta_dist_y;
	}
}

static void	hit_distance(t_sys *sys)
{
	bool	hit;

	hit = false;
	while (!hit)
	{
		if (sys->rayhit.side_dist_x < sys->rayhit.side_dist_y)
		{
			sys->rayhit.side_dist_x += sys->rayhit.delta_dist_x;
			sys->rayhit.map_x += sys->rayhit.step_x;
			sys->rayhit.orientation = 0;
		}
		else
		{
			sys->rayhit.side_dist_y += sys->rayhit.delta_dist_y;
			sys->rayhit.map_y += sys->rayhit.step_y;
			sys->rayhit.orientation = 1;
		}
		if (sys->map_sys.game_map[sys->rayhit.map_y][sys->rayhit.map_x] == '1')
			hit = true;
	}
}

static void	exact_distance(t_sys *sys)
{
	if (sys->rayhit.orientation == 0)
	{
		sys->rayhit.distance = (sys->rayhit.map_x - sys->pos_x
				+ (1 - sys->rayhit.step_x) / 2) / sys->rayhit.delta_x;
		sys->rayhit.hit_x = sys->pos_x + sys->rayhit.distance
			* sys->rayhit.delta_x;
		sys->rayhit.hit_y = sys->pos_y + sys->rayhit.distance
			* sys->rayhit.delta_y;
		set_side(sys, 'x');
	}
	else
	{
		sys->rayhit.distance = (sys->rayhit.map_y - sys->pos_y
				+ (1 - sys->rayhit.step_y) / 2) / sys->rayhit.delta_y;
		sys->rayhit.hit_x = sys->pos_x + sys->rayhit.distance
			* sys->rayhit.delta_x;
		sys->rayhit.hit_y = sys->pos_y + sys->rayhit.distance
			* sys->rayhit.delta_y;
		set_side(sys, 'y');
	}
}

void	distance_raycasting(t_sys *sys, double angle)
{
	angle = angle * (M_PI / 180);
	init_raycasting(sys, angle);
	step_side_distance(sys);
	hit_distance(sys);
	exact_distance(sys);
	sys->rayhit.distance = sys->rayhit.distance * cos(angle - (double)sys->dir
			* (M_PI / 180));
}
