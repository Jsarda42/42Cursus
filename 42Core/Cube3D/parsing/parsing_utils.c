/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edegraev <edegraev@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:37:23 by jsarda            #+#    #+#             */
/*   Updated: 2024/08/27 15:03:47 by edegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_count_args(char **arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (0);
	while (arg[i])
		i++;
	return (i);
}

void	check_args_nbr(t_sys *sys, char **str, int nbr)
{
	if (ft_count_args(str) != nbr)
	{
		free_split(str);
		ft_errors(sys, "Cardinal : wrong number of arguments", 1);
	}
}

int	is_identifier(char identifier)
{
	if (identifier == 'N' || identifier == 'S' || identifier == 'W'
		|| identifier == 'E' || identifier == 'C' || identifier == 'F')
		return (1);
	return (0);
}
