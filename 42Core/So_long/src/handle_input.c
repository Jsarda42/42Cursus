/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:53:55 by jsarda            #+#    #+#             */
/*   Updated: 2024/01/10 10:59:39 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_player(t_game *game, int new_x, int new_y)
{
	game->map.player.x = new_x;
	game->map.player.y = new_y;
	game->move_count++;
}

void	player_move(t_game *game, int new_y, int new_x, int player_texture)
{
	int	last_x;
	int	last_y;

	last_x = game->map.player.x;
	last_y = game->map.player.y;
	game->player_texture = player_texture;
	if (game->map.map_tab[new_y][new_x] == EXIT && game->map.coins_count == 0)
	{
		game->map.map_tab[new_y][new_x] = PLAYER;
		move_player(game, new_x, new_y);
		victory(game);
	}
	else if (game->map.map_tab[new_y][new_x] == FLOOR
		|| game->map.map_tab[new_y][new_x] == COINS)
	{
		game->map.map_tab[last_y][last_x] = FLOOR;
		if (game->map.map_tab[new_y][new_x] == COINS)
			game->map.coins_count--;
		move_player(game, new_x, new_y);
		game->map.map_tab[new_y][new_x] = PLAYER;
	}
	render_map(game);
}

int	handle_input(int keysym, t_game *game)
{
	if (keysym == KEY_DOWN || keysym == KEY_S)
		player_move(game, game->map.player.y + 1, game->map.player.x, BACK);
	if (keysym == KEY_UP || keysym == KEY_W)
		player_move(game, game->map.player.y - 1, game->map.player.x, TOP);
	if (keysym == KEY_LEFT || keysym == KEY_A)
		player_move(game, game->map.player.y, game->map.player.x - 1, LEFT);
	if (keysym == KEY_RIGHT || keysym == KEY_D)
		player_move(game, game->map.player.y, game->map.player.x + 1, RIGHT);
	if (keysym == KEY_ESC || keysym == KEY_Q)
		close_game(game);
	return (0);
}
