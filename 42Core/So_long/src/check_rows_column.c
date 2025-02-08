/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rows_column.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 14:25:07 by jsarda            #+#    #+#             */
/*   Updated: 2024/01/10 10:28:36 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_r_c_parsing(t_game *game, char *trimmed_line, int fd)
{
	if (!game->map.columns)
		game->map.columns = (int)ft_strlen(trimmed_line);
	else if (game->map.columns != (int)ft_strlen(trimmed_line))
	{
		free(trimmed_line);
		free_all(game);
		end_file(fd);
		close(fd);
		error_failure_message("need to be rectangular");
	}
}
