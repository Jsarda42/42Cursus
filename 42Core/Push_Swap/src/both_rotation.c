/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   both_rotation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:26:40 by jsarda            #+#    #+#             */
/*   Updated: 2024/01/23 16:20:15 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	both_rotate(t_list **stack_a, t_list **stack_b, t_list *cheapest)
{
	while (*stack_a != cheapest && *stack_b != cheapest->target)
		rr(stack_a, stack_b);
}

void	both_rotate_reverse(t_list **stack_a, t_list **stack_b,
		t_list *cheapest)
{
	while (*stack_a != cheapest && *stack_b != cheapest->target)
		rrr(stack_a, stack_b);
}

void	normal_rotation(t_list **stack_a, t_list **stack_b)
{
	t_list	*cheapest;
	int		pos_a;
	int		pos_b;

	cheapest = cheapest_node(stack_a, stack_b);
	pos_a = get_node_position(*stack_a, cheapest);
	pos_b = get_node_position(*stack_b, cheapest->target);
	if (way_to_move(stack_a, pos_a))
		while (*stack_a != cheapest)
			ra(stack_a);
	else
		while (*stack_a != cheapest)
			rra(stack_a);
	if (way_to_move(stack_b, pos_b))
		while (*stack_b != cheapest->target)
			rb(stack_b);
	else
		while (*stack_b != cheapest->target)
			rrb(stack_b);
}
