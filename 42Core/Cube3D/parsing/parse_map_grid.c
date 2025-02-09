/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_grid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edegraev <edegraev@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:48:47 by jsarda            #+#    #+#             */
/*   Updated: 2024/08/27 15:05:31 by edegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_first_line(t_sys *sys, char *line)
{
	int	i;

	if (!line)
		ft_errors(sys, "Map is empty", -42);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1')
			ft_errors(sys, "Wrong map format in first line", -42);
		i++;
	}
	return ;
}

int	check_last_line(t_sys *sys, char **map, int last)
{
	int	y;

	if (!map[last])
		last = last - 1;
	while (map[last])
	{
		y = 0;
		while (map[last][y])
		{
			ext_valid_char(sys, map[last][y]);
			if (map[last][y] == '1')
			{
				y = 0;
				while (map[last][y])
				{
					ext_valid_char(sys, map[last][y]);
					y++;
				}
				return (last);
			}
			y++;
		}
		last--;
	}
	return (last);
}

void	validate_map_position(t_sys *sys, char **map, int row, int col)
{
	if (map[row][col] == '0' || is_player_position(map[row][col]))
	{
		if (row == 0 || !map[row - 1][col] || map[row - 1][col] == ' ')
			ft_errors(sys, "Wrong map format in mid 1", -42);
		if (!map[row + 1] || map[row + 1][col] == ' ' || map[row
			+ 1][col] == '\0')
			ft_errors(sys, "Wrong map format in mid 2", -42);
		if (col == 0 || map[row][col - 1] == ' ')
			ft_errors(sys, "Wrong map format in mid 3", -42);
		if (!map[row][col + 1] || map[row][col + 1] == ' ' || map[row][col
			+ 1] == '\0')
			ft_errors(sys, "Wrong map format in mid 4", -42);
	}
}

int	check_mid_line(t_sys *sys, int row)
{
	int	col;
	int	player_number;

	player_number = 0;
	col = -1;
	if (sys->map_sys.game_map[row][0] == '\0')
		ft_errors(sys, "Wrong map format in mid 1", -42);
	while (sys->map_sys.game_map[row][++col])
	{
		process_player_position(sys, row, col, &player_number);
		mid_valid_char(sys, sys->map_sys.game_map[row][col]);
		validate_map_position(sys, sys->map_sys.game_map, row, col);
	}
	return (player_number);
}

void	parse_map_grid(t_sys *sys)
{
	int	last;
	int	row;
	int	player_number;
	int	i;

	i = 0;
	row = 1;
	player_number = 0;
	last = 0;
	check_first_line(sys, sys->map_sys.game_map[i]);
	while (sys->map_sys.game_map[last])
		last++;
	last = check_last_line(sys, sys->map_sys.game_map, last);
	while (row <= last - 1)
	{
		player_number += check_mid_line(sys, row);
		if (player_number > 1)
			ft_errors(sys, "Too many players", -42);
		row++;
	}
	if (player_number == 0)
		ft_errors(sys, "1 player needed", -42);
}
