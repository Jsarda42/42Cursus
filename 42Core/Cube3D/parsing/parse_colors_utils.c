/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:08:17 by jsarda            #+#    #+#             */
/*   Updated: 2024/08/27 14:10:41 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	extract_color(char *color_str)
{
	int	i;

	i = 0;
	color_str[ft_strlen(color_str) - 1] = '\0';
	while (color_str[i] == ' ')
		i++;
	return (ft_atoi(&color_str[i]));
}

int	parse_rgb_value(char *colors_line, int *i)
{
	int	value;

	value = 0;
	while (colors_line[*i] == ' ')
		(*i)++;
	if (!ft_isdigit(colors_line[*i]))
		return (-1);
	while (ft_isdigit(colors_line[*i]))
	{
		value = value * 10 + (colors_line[*i] - '0');
		if (value > 255)
			return (-1);
		(*i)++;
	}
	while (colors_line[*i] == ' ')
		(*i)++;
	return (value);
}

int	valid_rgb(char *colors_line, int *i)
{
	int	count;
	int	comma_count;
	int	value;

	count = 0;
	comma_count = -1;
	while (colors_line[*i])
	{
		value = parse_rgb_value(colors_line, i);
		if (value == -1)
			return (0);
		count++;
		if (comma_count++ != -2 && count < 3)
		{
			if (colors_line[(*i)++] != ',')
				return (0);
		}
		else if (count == 3)
		{
			if (colors_line[*i] == ',')
				return (0);
			break ;
		}
	}
	return (count == 3 && comma_count == 2);
}
