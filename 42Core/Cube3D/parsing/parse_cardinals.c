/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cardinals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:47:15 by jsarda            #+#    #+#             */
/*   Updated: 2024/08/21 12:26:27 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_cardinal_format(t_sys *sys, char **cardinal)
{
	int	i;

	i = 0;
	while (cardinal[0][i] == ' ')
		i++;
	if ((cardinal[0][i] == 'N' && cardinal[0][i + 1] == 'O')
		|| (cardinal[0][i] == 'W' && cardinal[0][i + 1] == 'E')
		|| (cardinal[0][i] == 'S' && cardinal[0][i + 1] == 'O')
		|| (cardinal[0][i] == 'E' && cardinal[0][i + 1] == 'A'))
	{
		if (cardinal[0][i + 2] != '\0' && cardinal[0][i + 2] != ' ')
		{
			free_split(cardinal);
			ft_errors(sys, "Wrong cardinal format", 1);
		}
	}
	else
	{
		free_split(cardinal);
		ft_errors(sys, "Wrong cardinal", 1);
	}
}

void	assign_cardinal_texture(t_sys *sys, char **cardinal)
{
	int	i;

	i = 0;
	while (cardinal[0][i] == ' ')
		i++;
	if (cardinal[0][i] == 'N' && cardinal[0][i + 1] == 'O'
		&& !sys->no_wall.img_filename)
		sys->no_wall.img_filename = ft_strdup(cardinal[1]);
	else if (cardinal[0][i] == 'W' && cardinal[0][i + 1] == 'E'
		&& !sys->we_wall.img_filename)
		sys->we_wall.img_filename = ft_strdup(cardinal[1]);
	else if (cardinal[0][i] == 'S' && cardinal[0][i + 1] == 'O'
		&& !sys->so_wall.img_filename)
		sys->so_wall.img_filename = ft_strdup(cardinal[1]);
	else if (cardinal[0][i] == 'E' && cardinal[0][i + 1] == 'A'
		&& !sys->ea_wall.img_filename)
		sys->ea_wall.img_filename = ft_strdup(cardinal[1]);
}

void	parse_cardinals(t_sys *sys, char *cardinal_line)
{
	char	**cardinal;

	cardinal = ft_split(cardinal_line, ' ');
	if (ft_count_args(cardinal) != 2)
	{
		free_split(cardinal);
		ft_errors(sys, "Cardinal : wrong number of arguments", 1);
	}
	validate_cardinal_format(sys, cardinal);
	assign_cardinal_texture(sys, cardinal);
	free_split(cardinal);
}
