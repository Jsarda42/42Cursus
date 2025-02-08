/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval_format.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:09:26 by jsarda            #+#    #+#             */
/*   Updated: 2023/11/23 11:44:38 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_eval_format(va_list args, const char format)
{
	int	len;

	len = 0;
	if (format == 'c')
		len = len + ft_print_char(va_arg(args, int));
	else if (format == 's')
		len = len + ft_print_str(va_arg(args, char *));
	else if (format == 'p')
		len = len + ft_print_ptr(va_arg(args, unsigned long long));
	else if (format == 'd' || format == 'i')
		len = len + ft_print_nbr(va_arg(args, int));
	else if (format == 'u')
		len = len + ft_print_nbr_unsigned(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		len = len + ft_print_ptr_hexa(va_arg(args, unsigned int), format);
	else if (format == '%')
	{
		len = ft_print_char('%');
	}
	return (len);
}
