/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:47:15 by jsarda            #+#    #+#             */
/*   Updated: 2024/08/27 14:10:07 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	assign_colors(t_sys *sys, char **colors, char c)
{
	if (c == 'F')
	{
		sys->floor_color[0] = ft_atoi(colors[0]);
		sys->floor_color[1] = ft_atoi(colors[1]);
		sys->floor_color[2] = ft_atoi(colors[2]);
	}
	else
	{
		sys->ceil_color[0] = ft_atoi(colors[0]);
		sys->ceil_color[1] = ft_atoi(colors[1]);
		sys->ceil_color[2] = ft_atoi(colors[2]);
	}
}

void	check_line_args(t_sys *sys, char *colors_line)
{
	int	i;
	int	checker;

	checker = 0;
	i = 0;
	while (colors_line[i])
	{
		while (colors_line[i] == ' ')
			i++;
		if (colors_line[i] == 'C' || colors_line[i] == 'F')
		{
			if (colors_line[i + 1] != ' ')
				ft_errors(sys, "Identifier can only be C or F", -42);
			checker = checker + 1;
			if (checker > 1)
				ft_errors(sys, "Too many identifiers in color line", -42);
			i++;
		}
		if (!valid_rgb(colors_line, &i))
			ft_errors(sys, "Invalid RGB format", -42);
		while (colors_line[i] == ' ')
			i++;
		if (colors_line[i] != '\0')
			ft_errors(sys, "Invalid characters after RGB values", 1);
	}
}

void	parse_colors(t_sys *sys, char *colors_line, char c)
{
	char	**colors;
	char	*tmp;

	check_line_args(sys, colors_line);
	colors = ft_split(colors_line, ',');
	if (!colors)
		ft_errors(sys, "Failed to split the colors", 1);
	if (colors[0][0] == 'C' || colors[0][0] == 'F')
	{
		tmp = ft_strdup(&colors[0][1]);
		free(colors[0]);
		colors[0] = tmp;
	}
	assign_colors(sys, colors, c);
	free_split(colors);
}
