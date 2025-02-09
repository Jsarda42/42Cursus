/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:47:47 by jsarda            #+#    #+#             */
/*   Updated: 2024/08/27 14:31:50 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_map_size(int fd, t_sys *sys)
{
	char	*dummy;

	dummy = get_next_line(fd);
	sys->map_sys.map_size++;
	while (dummy)
	{
		free(dummy);
		dummy = get_next_line(fd);
		sys->map_sys.map_size++;
	}
	close(fd);
}

void	read_map(int fd, t_sys *sys, char *map_name)
{
	int	i;

	i = 0;
	get_map_size(fd, sys);
	sys->map_sys.map_str = ft_calloc(sys->map_sys.map_size + 1,
			sizeof(char **));
	if (!sys->map_sys.map_str)
		ft_errors(sys, strerror(errno), errno);
	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		ft_errors(sys, "Error opening file", 1);
	sys->map_sys.map_str[i] = get_next_line(fd);
	while (sys->map_sys.map_str[i] && i < sys->map_sys.map_size)
	{
		if (sys->map_sys.map_str[i][ft_strlen(sys->map_sys.map_str[i])
			- 1] == '\n')
			sys->map_sys.map_str[i][ft_strlen(sys->map_sys.map_str[i])
				- 1] = '\0';
		i++;
		sys->map_sys.map_str[i] = get_next_line(fd);
	}
	close(fd);
}

void	init_map(t_sys *sys)
{
	int		fd;
	char	*map_name;

	map_name = sys->map_sys.map_filename;
	if (ft_strlen(map_name) <= 4 || !ft_strnstr(map_name + (ft_strlen(map_name)
				- 4), ".cub", 5))
		ft_errors(sys,
			"File format must be 'exemple.cub' or file does not exist", 1);
	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		ft_errors(sys, "Error opening file", 1);
	read_map(fd, sys, map_name);
}
