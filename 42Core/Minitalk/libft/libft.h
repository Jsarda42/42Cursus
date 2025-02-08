/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:53:47 by jsarda            #+#    #+#             */
/*   Updated: 2024/02/05 13:00:55 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

int		ft_eval_format(va_list args, const char format);
int		ft_print_char(int c);
int		ft_print_nbr(int i);
int		ft_print_ptr_hexa(unsigned int ptr, char format);
int		ft_print_ptr(unsigned long long ptr);
int		ft_print_str(char *str);
int		ft_print_nbr_unsigned(unsigned int i);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_printf(const char *format, ...);
int		ft_atoi(const char *nptr);
void	*ft_realloc(void *ptr, size_t newsize);
void	*ft_memcpy(void *dest, const void *src, size_t n);

#endif
