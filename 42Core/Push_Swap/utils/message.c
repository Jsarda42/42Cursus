/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 09:21:16 by jsarda            #+#    #+#             */
/*   Updated: 2024/01/26 09:38:18 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/push_swap.h"

void	error_message(char *message, t_list **stack)
{
	ft_putendl_fd(message, 1);
	if (stack)
		clear_list(stack);
	exit(EXIT_FAILURE);
}
