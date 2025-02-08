/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:47:47 by jsarda            #+#    #+#             */
/*   Updated: 2023/11/23 13:32:09 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	ft_print_ptr(unsigned long long ptr)
{
	char	str[20];
	char	*base_character;
	size_t	len;
	size_t	i;

	base_character = "0123456789abcdef";
	i = 0;
	len = 0;
	if (ptr == 0)
	{
		return (write(1, "(nil)", 5));
	}
	else
	{
		write(1, "0x", 2);
		len = 2;
		while (ptr != 0)
		{
			str[i++] = base_character[ptr % 16];
			ptr = ptr / 16;
		}
		while (i--)
			len += ft_print_char(str[i]);
		return (len);
	}
}
