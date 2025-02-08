/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_target.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:07:21 by jsarda            #+#    #+#             */
/*   Updated: 2024/01/23 13:31:40 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_list	*get_max_target(t_list *stack)
{
	t_list	*max;
	t_list	*current;

	current = stack;
	max = stack;
	while (current)
	{
		if (current->data > max->data)
			max = current;
		current = current->next;
	}
	return (max);
}

t_list	*get_target(int current_a_data, t_list **stack_b)
{
	t_list	*current_b;
	t_list	*target;
	int		fit;

	target = NULL;
	current_b = *stack_b;
	if (current_b)
		fit = current_b->data;
	else
		fit = 0;
	while (current_b)
	{
		if (current_a_data > current_b->data)
		{
			if (fit < current_b->data || !target)
			{
				fit = current_b->data;
				target = current_b;
			}
		}
		current_b = current_b->next;
	}
	if (!target)
		target = get_max_target(*stack_b);
	return (target);
}

t_list	*get_min_target(t_list *stack)
{
	t_list	*min;

	min = stack;
	while (stack)
	{
		if (stack->data < min->data)
			min = stack;
		stack = stack->next;
	}
	return (min);
}

t_list	*get_target_closest_bigger(int current_a_data, t_list **stack)
{
	t_list	*current;
	t_list	*target;
	int		fit;

	target = NULL;
	current = *stack;
	if (current)
		fit = current->data;
	else
		fit = 0;
	while (current)
	{
		if (current_a_data < current->data)
		{
			if (fit > current->data || !target)
			{
				fit = current->data;
				target = current;
			}
		}
		current = current->next;
	}
	if (!target)
		target = get_min_target(*stack);
	return (target);
}
