/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edegraev <edegraev@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:27:12 by jsarda            #+#    #+#             */
/*   Updated: 2024/08/26 14:47:10 by edegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_walls(t_sys *sys)
{
	sys->ea_wall.h = -1;
	sys->no_wall.h = -1;
	sys->we_wall.h = -1;
	sys->so_wall.h = -1;
	sys->ea_wall.w = -1;
	sys->no_wall.w = -1;
	sys->we_wall.w = -1;
	sys->so_wall.w = -1;
	sys->no_wall.xpm_ptr = NULL;
	sys->so_wall.xpm_ptr = NULL;
	sys->we_wall.xpm_ptr = NULL;
	sys->ea_wall.xpm_ptr = NULL;
	sys->no_wall.img_data = NULL;
	sys->so_wall.img_data = NULL;
	sys->we_wall.img_data = NULL;
	sys->ea_wall.img_data = NULL;
	sys->no_wall.img_filename = NULL;
	sys->ea_wall.img_filename = NULL;
	sys->we_wall.img_filename = NULL;
	sys->so_wall.img_filename = NULL;
}

void	init_data(t_sys *sys, char **argv)
{
	sys->mlx_ptr = mlx_init();
	if (!sys->mlx_ptr)
		ft_errors(sys, "Error initialising mlx", 1);
	sys->map_sys.map_filename = argv[1];
	sys->map_sys.map_str = NULL;
	sys->map_sys.game_map = NULL;
	sys->map_sys.map_size = 0;
	sys->win_ptr = NULL;
	sys->img = NULL;
	sys->img_data = NULL;
	sys->s_h = 0;
	sys->s_w = 0;
	sys->key_x = 0;
	sys->key_y = 0;
	sys->key_dir = 0;
	sys->prev_mouse_x = 0;
	sys->dir = 0;
	sys->pos_x = -1;
	sys->pos_y = -1;
	init_walls(sys);
}
