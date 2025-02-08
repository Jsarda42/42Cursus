/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:47:02 by jsarda            #+#    #+#             */
/*   Updated: 2024/01/10 11:08:25 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	malloc_error_1(t_game *game, char *trimmed_line)
{
	free(game->map.map_tab);
	free(trimmed_line);
	error_failure_message("Memory allocation failed in init_map 1");
}

void	malloc_error_2(t_game *game, char *trimmed_line, int i)
{
	free(game->map.map_tab[i]);
	free(game->map.map_tab);
	free(trimmed_line);
	error_failure_message("Memory allocation failed in init_map 2");
}

static void	malloc_game_tab_3(t_game *game)
{
	int	i;

	i = 0;
	game->map.map_tab = malloc(sizeof(char *) * (game->map.rows + 1));
	if (!game->map.map_tab)
	{
		free(game->map.map_tab);
		error_failure_message("Memory allocation failed in init_map");
	}
	while (i < (game->map.rows + 1))
	{
		game->map.map_tab[i] = 0;
		i++;
	}
}

// get_next_line(-72) the leak from malloc 1 come from gnl
void	allocate_map_tab(t_game *game, int fd)
{
	int		i;
	char	*line;
	char	*trimmed_line;

	malloc_game_tab_3(game);
	i = -1;
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		trimmed_line = ft_strtrim(line, "\n");
		free(line);
		if (!trimmed_line)
			malloc_error_1(game, trimmed_line);
		if (++i < game->map.rows)
		{
			game->map.map_tab[i] = ft_strdup(trimmed_line);
			if (!game->map.map_tab[i])
				malloc_error_2(game, trimmed_line, i);
			check_r_c_parsing(game, trimmed_line, fd);
			free(trimmed_line);
		}
	}
}

void	init_map(t_game *game, const char *argv)
{
	int	fd;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		error_failure_message("Could not open the map make sure the map exist");
	allocate_map_tab(game, fd);
	close(fd);
}
