/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 09:39:05 by edegraev          #+#    #+#             */
/*   Updated: 2024/08/28 09:43:52 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_texture_x(t_sys *sys, int texture_width)
{
	int	texture_x;

	if (sys->rayhit.side == 0)
	{
		texture_x = (int)(sys->rayhit.hit_y * texture_width) % texture_width;
		if (texture_x < 0)
			texture_x += texture_width;
	}
	else
	{
		texture_x = (int)(sys->rayhit.hit_x * texture_width) % texture_width;
		if (texture_x < 0)
			texture_x += texture_width;
	}
	return (texture_x);
}
