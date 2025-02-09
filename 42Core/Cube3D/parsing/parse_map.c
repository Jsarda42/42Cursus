/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:00:15 by jsarda            #+#    #+#             */
/*   Updated: 2024/08/27 14:46:03 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_map(t_sys *sys)
{
	char	**map;
	int		i;
	int		j;
	int		game_map_len;

	game_map_len = 0;
	i = 0;
	j = 0;
	map = sys->map_sys.map_str;
	i = parse_identifier(sys, map);
	game_map_len = sys->map_sys.map_size - i;
	sys->map_sys.game_map = malloc(sizeof(char *) * game_map_len);
	if (!sys->map_sys.game_map)
		ft_errors(sys, "Malloc error", 1);
	while (j < game_map_len)
	{
		sys->map_sys.game_map[j] = ft_strdup(map[i + j]);
		j++;
	}
	parse_map_grid(sys);
}
