/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edegraev <edegraev@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:20:57 by achevron          #+#    #+#             */
/*   Updated: 2024/08/27 15:02:03 by edegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_keypress_down(int keysym, t_sys *sys)
{
	if (keysym == XK_Escape)
		mlx_loop_end(sys->mlx_ptr);
	else if (keysym == XK_W || keysym == XK_w)
		sys->key_x = 1;
	else if (keysym == XK_S || keysym == XK_s)
		sys->key_x = -1;
	else if (keysym == XK_A || keysym == XK_a)
		sys->key_y = -1;
	else if (keysym == XK_D || keysym == XK_d)
		sys->key_y = 1;
	else if (keysym == XK_Left)
		sys->key_dir = -1;
	else if (keysym == XK_Right)
		sys->key_dir = 1;
	return (0);
}

int	handle_keypress_up(int keysym, t_sys *sys)
{
	if (keysym == XK_W || keysym == XK_w || keysym == XK_S || keysym == XK_s)
		sys->key_x = 0;
	else if (keysym == XK_A || keysym == XK_a || keysym == XK_D
		|| keysym == XK_d)
		sys->key_y = 0;
	else if (keysym == XK_Left || keysym == XK_Right)
		sys->key_dir = 0;
	return (0);
}

bool	is_collision(t_sys *sys, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (sys->map_sys.game_map[map_y][map_x] == '1' ||
		sys->map_sys.game_map[map_y][(int)(x + COLLISION_MARGIN)] == '1' ||
		sys->map_sys.game_map[map_y][(int)(x - COLLISION_MARGIN)] == '1' ||
		sys->map_sys.game_map[(int)(y + COLLISION_MARGIN)][map_x] == '1' ||
		sys->map_sys.game_map[(int)(y - COLLISION_MARGIN)][map_x] == '1')
	{
		return (true);
	}
	return (false);
}

void	move_player(t_sys *sys)
{
	double	rad_dir;
	double	new_pos_x;
	double	new_pos_y;

	rad_dir = sys->dir * M_PI / 180.0;
	new_pos_x = sys->pos_x;
	new_pos_y = sys->pos_y;
	new_pos_x += sys->key_x * cos(rad_dir) * MOVE_SPEED;
	new_pos_y += sys->key_x * sin(rad_dir) * MOVE_SPEED;
	new_pos_x += sys->key_y * cos(rad_dir + M_PI_2) * MOVE_SPEED;
	new_pos_y += sys->key_y * sin(rad_dir + M_PI_2) * MOVE_SPEED;
	if (!is_collision(sys, new_pos_x, sys->pos_y))
		sys->pos_x = new_pos_x;
	if (!is_collision(sys, sys->pos_x, new_pos_y))
		sys->pos_y = new_pos_y;
	sys->dir += sys->key_dir * ROTATE_SPEED;
	if (sys->dir >= 360)
		sys->dir = 0;
	else if (sys->dir <= 0)
		sys->dir = 360;
}

int	close_window(t_sys *sys)
{
	int	closed;

	closed = mlx_loop_end(sys->mlx_ptr);
	return (closed);
}
