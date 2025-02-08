/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:31:02 by jsarda            #+#    #+#             */
/*   Updated: 2023/11/23 11:40:19 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int	ft_eval_format(va_list args, const char format);
int	ft_print_str(char *str);
int	ft_print_char(int c);
int	ft_print_nbr_unsigned(unsigned int i);
int	ft_print_nbr(int i);
int	ft_print_ptr(unsigned long long ptr);
int	ft_print_ptr_hexa(unsigned int i, const char format);
int	ft_printf(const char *format, ...);

#endif
