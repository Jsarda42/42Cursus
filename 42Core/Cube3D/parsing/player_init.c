/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:15:56 by jsarda            #+#    #+#             */
/*   Updated: 2024/08/27 14:27:33 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	get_player_dir(char c)
{
	if (c == 'E')
		return (0);
	if (c == 'N')
		return (270);
	if (c == 'W')
		return (180);
	if (c == 'S')
		return (90);
	return (0);
}

int	is_player_position(char c)
{
	if (c == 'E' || c == 'N' || c == 'W' || c == 'S')
		return (1);
	return (0);
}

void	process_player_position(t_sys *sys, int row, int col,
		int *player_number)
{
	if (is_player_position(sys->map_sys.game_map[row][col]))
	{
		*player_number += 1;
		sys->dir = get_player_dir(sys->map_sys.game_map[row][col]);
		sys->ply_pos_x = col;
		sys->ply_pos_y = row;
		sys->pos_x = col + 0.5;
		sys->pos_y = row + 0.5;
	}
}
