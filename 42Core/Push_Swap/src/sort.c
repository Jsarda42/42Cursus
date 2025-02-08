/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 11:27:59 by jsarda            #+#    #+#             */
/*   Updated: 2024/01/26 08:31:10 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	final_rotation(t_list **stack_a)
{
	t_list	*min;

	min = get_min_target(*stack_a);
	if (get_node_position(*stack_a, min) < get_median(stack_a))
		while (min->data != (*stack_a)->data)
			ra(stack_a);
	else
		while (min->data != (*stack_a)->data)
			rra(stack_a);
}

void	sort(t_list **stack_a, t_list **stack_b)
{
	int	stack_a_size;

	stack_a_size = ft_lstsize(*stack_a);
	if (stack_a_size <= 3)
		sort_3(stack_a);
	else
	{
		pb(stack_a, stack_b);
		pb(stack_a, stack_b);
		if (*stack_b < (*stack_b)->next)
			sb(stack_b);
		stack_a_size = ft_lstsize(*stack_a);
		while (stack_a_size > 3)
		{
			push_best_to_b(stack_a, stack_b);
			stack_a_size--;
		}
		if (!is_sorted(*stack_a))
			sort_3(stack_a);
		while (*stack_b)
			push_back_to_a(stack_a, stack_b);
		final_rotation(stack_a);
	}
}
