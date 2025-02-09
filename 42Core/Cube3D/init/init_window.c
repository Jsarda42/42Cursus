/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:01:03 by jsarda            #+#    #+#             */
/*   Updated: 2024/08/27 14:31:44 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_window(t_sys *sys)
{
	mlx_get_screen_size(sys->mlx_ptr, &sys->s_w, &sys->s_h);
	sys->win_ptr = mlx_new_window(sys->mlx_ptr, sys->s_w, sys->s_h, "cud3D");
	if (!sys->win_ptr)
		ft_errors(sys, "Failed to create window", -41);
}
