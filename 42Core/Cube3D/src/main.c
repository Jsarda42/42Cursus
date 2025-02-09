/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edegraev <edegraev@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:11:34 by jsarda            #+#    #+#             */
/*   Updated: 2024/08/27 15:14:48 by edegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_sys	sys;

	if (argc != 2)
		return (write(2, "Wrong number of arguments\n", 27), 194);
	init_data(&sys, argv);
	init_map(&sys);
	parse_map(&sys);
	init_textures(&sys);
	init_window(&sys);
	mlx_hook(sys.win_ptr, KeyPress, KeyPressMask, &handle_keypress_down, &sys);
	mlx_hook(sys.win_ptr, KeyRelease, KeyReleaseMask, &handle_keypress_up,
		&sys);
	mlx_hook(sys.win_ptr, DestroyNotify, StructureNotifyMask, &close_game,
		&sys);
	sys.img = mlx_new_image(sys.mlx_ptr, sys.s_w, sys.s_h);
	sys.img_data = mlx_get_data_addr(sys.img, &sys.bpp, &sys.size_line,
			&sys.endian);
	mlx_loop_hook(sys.mlx_ptr, update_screen, &sys);
	mlx_loop(sys.mlx_ptr);
	free_all(&sys);
	return (0);
}
