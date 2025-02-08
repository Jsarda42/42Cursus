/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:06:22 by jsarda            #+#    #+#             */
/*   Updated: 2024/01/10 11:02:07 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	init_textures(t_game *game)
{
	game->wall.xpm_ptr = NULL;
	game->floor.xpm_ptr = NULL;
	game->coins.xpm_ptr = NULL;
	game->player_top.xpm_ptr = NULL;
	game->player_left.xpm_ptr = NULL;
	game->player_right.xpm_ptr = NULL;
	game->player_back.xpm_ptr = NULL;
	game->exit_close.xpm_ptr = NULL;
	game->exit_open.xpm_ptr = NULL;
}

void	init_values(t_game *game, char *argv)
{
	init_textures(game);
	game->map.map_tab = NULL;
	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->map.rows = 0;
	game->texture = 0;
	get_rows_len(game, argv);
	game->map.columns = 0;
	game->map_alloc = false;
	game->player_texture = RIGHT;
	game->map.coins_count = 0;
	game->map.exit = 0;
	game->move_count = 0;
	game->map.players = 0;
}
