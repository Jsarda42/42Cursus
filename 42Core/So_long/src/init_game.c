/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 00:14:24 by juliensarda       #+#    #+#             */
/*   Updated: 2024/01/10 10:56:19 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_screen_size(t_game *game)
{
	int	screen_height;
	int	screen_width;

	screen_height = 0;
	screen_width = 0;
	mlx_get_screen_size(game->mlx_ptr, &screen_width, &screen_height);
	if (!game->map.rows * TEXTURE_HEIGHT > screen_height || game->map.columns
		* TEXTURE_HEIGHT > screen_width)
	{
		free_all(game);
		error_failure_message("The map is too big compare to the screen size");
	}
}

void	init_new_window(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
	{
		free_all(game);
		error_failure_message("Error getting the mlx-ptr");
	}
	check_screen_size(game);
	game->win_ptr = mlx_new_window(game->mlx_ptr, game->map.columns
			* TEXTURE_WIDTH, game->map.rows * TEXTURE_HEIGHT, "42 so_long");
	if (!game->win_ptr)
	{
		free_all(game);
		error_failure_message("Fail to open the new window");
	}
}

t_image	new_texture(t_game *game, void *mlx, char *path)
{
	t_image	texture;

	texture.xpm_ptr = mlx_xpm_file_to_image(mlx, path, &texture.x, &texture.y);
	if (!texture.xpm_ptr)
	{
		free_all(game);
		error_failure_message("Couldn't find any texture.");
	}
	return (texture);
}

void	init_texture(t_game *game)
{
	game->wall = new_texture(game, game->mlx_ptr, WALL_XPM);
	game->coins = new_texture(game, game->mlx_ptr, COINS_XPM);
	game->player_right = new_texture(game, game->mlx_ptr, PLAYER_RIGHT_XPM);
	game->player_left = new_texture(game, game->mlx_ptr, PLAYER_LEFT_XPM);
	game->player_top = new_texture(game, game->mlx_ptr, PLAYER_TOP_XPM);
	game->player_back = new_texture(game, game->mlx_ptr, PLAYER_BACK_XPM);
	game->exit_open = new_texture(game, game->mlx_ptr, EXIT_OPEN_XPM);
	game->floor = new_texture(game, game->mlx_ptr, FLOOR_XPM);
	game->exit_close = new_texture(game, game->mlx_ptr, EXIT_CLOSE_XPM);
	game->texture = 1;
}
