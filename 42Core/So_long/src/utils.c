/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 10:52:49 by juliensarda       #+#    #+#             */
/*   Updated: 2024/01/09 14:06:58 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_failure_message(char *message)
{
	ft_printf("%s\n", message);
	exit(EXIT_FAILURE);
}

void	get_rows_len(t_game *game, char *argv)
{
	int		fd;
	char	*line;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		error_failure_message("Could not open the map, \
		make sure the map exist");
	game->map.rows = 0;
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
		{
			free(line);
			break ;
		}
		game->map.rows++;
		free(line);
	}
	close(fd);
}

void	print_movements(t_game *game)
{
	char	*movements;
	char	*phrase;

	movements = ft_itoa(game->move_count);
	phrase = ft_strjoin("Movements : ", movements);
	mlx_string_put(game->mlx_ptr, game->win_ptr, 40, 20, 0xFFFFFF, phrase);
	free(movements);
	free(phrase);
}

void	check_command_line_arguments(int argc, char **argv)
{
	int	map_parameter_len;

	if (argc > 2)
		error_failure_message("Too many arguments \
		(It should be only two).");
	if (argc < 2)
		error_failure_message("The Map file is missing.");
	map_parameter_len = ft_strlen(argv[1]);
	if (!ft_strnstr(&argv[1][map_parameter_len - 4], ".ber", 4))
		error_failure_message("Map file extention is wrong \
		(It should be .ber).");
}
