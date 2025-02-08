/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:48:39 by jsarda            #+#    #+#             */
/*   Updated: 2024/01/23 09:28:12 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_3(t_list **stack_a)
{
	int	biggest;

	biggest = get_max(*stack_a);
	if ((*stack_a)->data == biggest)
		ra(stack_a);
	else if ((*stack_a)->next->data == biggest)
		rra(stack_a);
	if ((*stack_a)->data > (*stack_a)->next->data)
		sa(stack_a);
}
