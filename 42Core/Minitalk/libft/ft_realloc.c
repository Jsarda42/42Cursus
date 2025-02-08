/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:36:15 by jsarda            #+#    #+#             */
/*   Updated: 2024/02/05 15:23:31 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t new_size)
{
	void	*new_ptr;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (ptr);
	new_ptr = malloc(new_size);
	ft_memcpy(new_ptr, ptr, new_size);
	return (new_ptr);
}
