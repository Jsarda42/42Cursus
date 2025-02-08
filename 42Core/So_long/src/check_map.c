/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 07:21:11 by jsarda            #+#    #+#             */
/*   Updated: 2024/01/10 11:03:51 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	unit_count_param(t_game *game, int y, int x)
{
	if (game->map.map_tab[y][x] == PLAYER)
	{
		game->map.players++;
		game->map.player.x = x;
		game->map.player.y = y;
	}
}

void	count_map_parameters(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y < game->map.rows)
	{
		x = -1;
		while (++x < game->map.columns)
		{
			if (!ft_strchr("CEP01", game->map.map_tab[y][x]))
			{
				free_all(game);
				error_failure_message("Invalid map parameter only CEP01");
			}
			unit_count_param(game, y, x);
			if (game->map.map_tab[y][x] == COINS)
				game->map.coins_count++;
			if (game->map.map_tab[y][x] == EXIT)
				game->map.exit++;
		}
	}
}

void	check_rows(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.rows)
	{
		if (game->map.map_tab[i][0] != WALL)
		{
			free_all(game);
			error_failure_message("Invalid Map the map need to be \
			sourounded by walls");
		}
		else if (game->map.map_tab[i][game->map.columns - 1] != WALL)
		{
			free_all(game);
			error_failure_message("Invalid Map the map need to be \
			sourounded by walls");
		}
		i++;
	}
}

void	check_columns(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.columns)
	{
		if (game->map.map_tab[0][i] != WALL)
		{
			free_all(game);
			error_failure_message("Invalid Map the map need to be \
			sourounded by walls");
		}
		else if (game->map.map_tab[game->map.rows - 1][i] != WALL)
		{
			free_all(game);
			error_failure_message("Invalid Map the map need to be \
			sourounded by walls");
		}
		i++;
	}
}

void	check_map(t_game *game)
{
	check_columns(game);
	check_rows(game);
	count_map_parameters(game);
	set_param_rules(game);
	is_path_available(game);
}
