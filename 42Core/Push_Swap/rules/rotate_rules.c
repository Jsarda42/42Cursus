/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_rules.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliensarda <juliensarda@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 10:24:18 by jsarda            #+#    #+#             */
/*   Updated: 2024/01/18 13:29:38 by juliensarda      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/push_swap.h"

static int	rotate(t_list **stack)
{
	t_list	*head;

	if (ft_lstsize(*stack) < 2)
		return (-1);
	head = *stack;
	*stack = head->next;
	head->next = NULL;
	ft_lstadd_back(stack, head);
	return (0);
}

int	ra(t_list **stack_a)
{
	if (rotate(stack_a) == -1)
		return (-1);
	ft_putendl_fd("ra", 1);
	return (0);
}

int	rb(t_list **stack_b)
{
	if (rotate(stack_b) == -1)
		return (-1);
	ft_putendl_fd("rb", 1);
	return (0);
}

int	rr(t_list **stack_a, t_list **stack_b)
{
	if (rotate(stack_a) == -1 || rotate(stack_b) == -1)
		return (-1);
	ft_putendl_fd("rr", 1);
	return (0);
}
