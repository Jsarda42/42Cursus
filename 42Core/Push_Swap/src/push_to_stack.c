/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_to_stack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:28:54 by jsarda            #+#    #+#             */
/*   Updated: 2024/01/23 16:45:04 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_best_to_b(t_list **stack_a, t_list **stack_b)
{
	t_list	*cheapest;
	int		i;
	int		pos_a;
	int		pos_b;

	i = 0;
	cheapest = cheapest_node(stack_a, stack_b);
	pos_a = get_node_position(*stack_a, cheapest);
	pos_b = get_node_position(*stack_b, cheapest->target);
	if (way_to_move(stack_a, pos_a) && way_to_move(stack_b, pos_b))
		both_rotate(stack_a, stack_b, cheapest);
	else if (!(way_to_move(stack_a, pos_a)) && !(way_to_move(stack_b, pos_b)))
		both_rotate_reverse(stack_a, stack_b, cheapest);
	normal_rotation(stack_a, stack_b);
	pb(stack_a, stack_b);
}

void	push_back_to_a(t_list **stack_a, t_list **stack_b)
{
	t_list	*target;
	int		pos;

	target = get_target_closest_bigger((*stack_b)->data, stack_a);
	pos = get_node_position(*stack_a, target);
	if (way_to_move(stack_a, pos))
		while (*stack_a != target)
			ra(stack_a);
	else
		while (*stack_a != target)
			rra(stack_a);
	pa(stack_b, stack_a);
}
