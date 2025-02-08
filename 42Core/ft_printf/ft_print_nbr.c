/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:47:28 by jsarda            #+#    #+#             */
/*   Updated: 2023/11/23 13:31:42 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_nbr(int i)
{
	int	count;

	count = 0;
	if (i == -2147483648)
		return (write(1, "-2147483648", 11));
	if (i < 0)
	{
		ft_print_char('-');
		count++;
		i = -i;
	}
	if (i >= 10)
	{
		count = count + ft_print_nbr(i / 10);
		count = count + ft_print_nbr(i % 10);
	}
	else
	{
		ft_print_char(i + 48);
		count++;
	}
	return (count);
}
