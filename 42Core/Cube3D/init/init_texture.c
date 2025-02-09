/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:10:25 by juliensarda       #+#    #+#             */
/*   Updated: 2024/08/27 14:31:47 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	file_to_img(t_image *image, t_sys *sys, char *filename)
{
	image->xpm_ptr = mlx_xpm_file_to_image(sys->mlx_ptr, filename, &(image->w),
			&(image->h));
	if (!image->xpm_ptr)
		ft_errors(sys, "Error uploading xpm to image", 1);
	image->img_data = mlx_get_data_addr(image->xpm_ptr, &image->bpp,
			&image->size_line, &image->endian);
}

static void	init_walls(t_sys *sys)
{
	if (!sys->no_wall.xpm_ptr)
		file_to_img(&(sys->no_wall), sys, sys->no_wall.img_filename);
	if (!sys->so_wall.xpm_ptr)
		file_to_img(&(sys->so_wall), sys, sys->so_wall.img_filename);
	if (!sys->we_wall.xpm_ptr)
		file_to_img(&(sys->we_wall), sys, sys->we_wall.img_filename);
	if (!sys->ea_wall.xpm_ptr)
		file_to_img(&(sys->ea_wall), sys, sys->ea_wall.img_filename);
}

void	init_textures(t_sys *sys)
{
	init_walls(sys);
}
