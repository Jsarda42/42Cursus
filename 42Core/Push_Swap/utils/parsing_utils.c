/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 09:07:09 by jsarda            #+#    #+#             */
/*   Updated: 2024/01/26 12:26:48 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/push_swap.h"

t_bool	is_valid_int(char *arg)
{
	int			i;
	long long	num;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i])
			&& arg[i] != ' ' && !(arg[i] == '+' || arg[i] == '-'))
			return (false);
		i++;
	}
	num = ft_atocoi(arg);
	if (num > INT_MAX || num < INT_MIN)
		return (false);
	arg++;
	return (true);
}
