/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 08:30:28 by jsarda            #+#    #+#             */
/*   Updated: 2024/01/10 10:55:35 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	destroy_textures(t_game *game)
{
	if (game->wall.xpm_ptr)
		mlx_destroy_image(game->mlx_ptr, game->wall.xpm_ptr);
	if (game->floor.xpm_ptr)
		mlx_destroy_image(game->mlx_ptr, game->floor.xpm_ptr);
	if (game->coins.xpm_ptr)
		mlx_destroy_image(game->mlx_ptr, game->coins.xpm_ptr);
	if (game->player_top.xpm_ptr)
		mlx_destroy_image(game->mlx_ptr, game->player_top.xpm_ptr);
	if (game->player_left.xpm_ptr)
		mlx_destroy_image(game->mlx_ptr, game->player_left.xpm_ptr);
	if (game->player_right.xpm_ptr)
		mlx_destroy_image(game->mlx_ptr, game->player_right.xpm_ptr);
	if (game->player_back.xpm_ptr)
		mlx_destroy_image(game->mlx_ptr, game->player_back.xpm_ptr);
}

void	destroy_textures2(t_game *game)
{
	if (game->exit_close.xpm_ptr)
		mlx_destroy_image(game->mlx_ptr, game->exit_close.xpm_ptr);
	if (game->exit_open.xpm_ptr)
		mlx_destroy_image(game->mlx_ptr, game->exit_open.xpm_ptr);
}

void	free_string(char **str, int i)
{
	int	j;

	j = 0;
	while (i > j)
	{
		if (str[j])
			free(str[j]);
		j++;
	}
	free(str);
	str = NULL;
}

void	free_string_2(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_all(t_game *game)
{
	int	i;

	i = game->map.rows;
	if (game->map.map_tab)
		free_string(game->map.map_tab, i);
	if (game->mlx_ptr)
	{
		destroy_textures(game);
		destroy_textures2(game);
	}
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
}
