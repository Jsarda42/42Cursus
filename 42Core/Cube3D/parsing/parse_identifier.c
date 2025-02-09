/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_identifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edegraev <edegraev@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:47:15 by jsarda            #+#    #+#             */
/*   Updated: 2024/08/27 15:05:53 by edegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	define_wrong_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	while (line[i])
	{
		if (line[i] != 'N' && line[i] != 'S' && line[i] != 'W'
			&& line[i] != 'E')
			return (1);
		i++;
	}
	return (0);
}

int	define_first_line(char *line)
{
	int	has_seen_one;
	int	i;

	if (!line)
		return (0);
	i = 0;
	has_seen_one = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		else if (line[i] == '1')
		{
			has_seen_one = 1;
			i++;
		}
		else
			break ;
	}
	return (has_seen_one);
}

void	check_number_of_identifier(t_sys *sys, int *identifier)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (identifier[i++] != 1)
			ft_errors(sys, "Wrong identifier or duplicate/not enough", 2);
	}
}

int	process_line(char *line, t_sys *sys, int *identifier, char c)
{
	if (c == 'C' || c == 'F')
	{
		if (c == 'C')
			parse_colors(sys, line, 'C');
		else
			parse_colors(sys, line, 'F');
		if (c == 'C')
			return (identifier[0]++, 1);
		else
			return (identifier[1]++, 1);
	}
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		parse_cardinals(sys, line);
		if (c == 'N')
			identifier[2]++;
		else if (c == 'S')
			identifier[3]++;
		else if (c == 'E')
			identifier[4]++;
		else
			identifier[5]++;
		return (1);
	}
	return (0);
}

int	parse_identifier(t_sys *sys, char **map)
{
	int			i;
	int			j;
	static int	identifier[6] = {0};

	if (!map)
		ft_errors(sys, "Map is empty", 2);
	i = 0;
	while (map[i])
	{
		j = 0;
		if (define_first_line(map[i]) != 0)
			break ;
		while (map[i][j] == ' ')
			j++;
		if (map[i][j] && !process_line(map[i], sys, identifier, map[i][j]))
			ft_errors(sys, "Wrong identifier", 2);
		i++;
	}
	check_number_of_identifier(sys, identifier);
	return (i);
}
