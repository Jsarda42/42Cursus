/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edegraev <edegraev@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:26:50 by jsarda            #+#    #+#             */
/*   Updated: 2024/08/27 15:07:04 by edegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	del_data(t_sys *sys)
{
	if (!sys)
		return ;
	if (sys->map_sys.map_str)
		free_split(sys->map_sys.map_str);
	if (sys->map_sys.game_map)
		free_split(sys->map_sys.game_map);
}

void	free_xpm_ptr(t_image *image, t_sys *sys)
{
	if (image->xpm_ptr)
		mlx_destroy_image(sys->mlx_ptr, image->xpm_ptr);
}

void	free_all(t_sys *sys)
{
	if (!sys)
		return ;
	del_data(sys);
	free_xpm_ptr(&(sys->no_wall), sys);
	free_xpm_ptr(&(sys->we_wall), sys);
	free_xpm_ptr(&(sys->so_wall), sys);
	free_xpm_ptr(&(sys->ea_wall), sys);
	if (sys->img)
		mlx_destroy_image(sys->mlx_ptr, sys->img);
	if (sys->no_wall.img_filename)
		free(sys->no_wall.img_filename);
	if (sys->so_wall.img_filename)
		free(sys->so_wall.img_filename);
	if (sys->we_wall.img_filename)
		free(sys->we_wall.img_filename);
	if (sys->ea_wall.img_filename)
		free(sys->ea_wall.img_filename);
	if (sys->win_ptr)
		mlx_destroy_window(sys->mlx_ptr, sys->win_ptr);
	if (sys->mlx_ptr)
	{
		mlx_destroy_display(sys->mlx_ptr);
		free(sys->mlx_ptr);
	}
}
