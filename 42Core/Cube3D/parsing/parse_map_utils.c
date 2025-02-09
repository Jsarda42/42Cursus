/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:39:18 by jsarda            #+#    #+#             */
/*   Updated: 2024/08/21 12:31:27 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mid_valid_char(t_sys *sys, char c)
{
	if (c == '1')
		return ;
	if (c == '0')
		return ;
	if (c == ' ')
		return ;
	if (c == 'E' || c == 'N' || c == 'W' || c == 'S')
		return ;
	ft_errors(sys, "Wrong character in mid line", -42);
}

void	ext_valid_char(t_sys *sys, char c)
{
	if (c == ' ')
		return ;
	if (c == '1')
		return ;
	ft_errors(sys, "Wrong character in extern line", -42);
}
