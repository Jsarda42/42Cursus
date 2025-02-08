/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr_unsigned.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:31:30 by jsarda            #+#    #+#             */
/*   Updated: 2024/01/30 15:53:00 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_nbr_unsigned(unsigned int i)
{
	int	count;

	count = 0;
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
