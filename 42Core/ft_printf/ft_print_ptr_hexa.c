/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr_hexa.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:53:33 by jsarda            #+#    #+#             */
/*   Updated: 2023/11/23 11:14:31 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_ptr_hexa(unsigned int ptr, char format)
{
	char	str[20];
	char	*base_character;
	int		i;
	int		len;

	len = 0;
	i = 0;
	if (format == 'x')
		base_character = "0123456789abcdef";
	if (format == 'X')
		base_character = "0123456789ABCDEF";
	if (ptr == 0)
		return (ft_print_char('0'));
	while (ptr != 0)
	{
		str[i++] = base_character[ptr % 16];
		ptr = ptr / 16;
	}
	while (i--)
	{
		ft_print_char(str[i]);
		len++;
	}
	return (len);
}
