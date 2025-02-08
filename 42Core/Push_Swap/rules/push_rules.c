/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_rules.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliensarda <juliensarda@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 16:47:17 by jsarda            #+#    #+#             */
/*   Updated: 2024/01/18 13:29:14 by juliensarda      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/push_swap.h"

static int	push(t_list **stack_src, t_list **stack_dest)
{
	t_list	*current_src;
	t_list	*current_dest;
	t_list	*tmp;

	if (ft_lstsize(*stack_src) == 0)
		return (-1);
	current_src = *stack_src;
	current_dest = *stack_dest;
	tmp = current_src;
	current_src = current_src->next;
	*stack_src = current_src;
	if (!current_dest)
	{
		current_dest = tmp;
		current_dest->next = NULL;
		*stack_dest = current_dest;
	}
	else
	{
		tmp->next = current_dest;
		*stack_dest = tmp;
	}
	return (0);
}

int	pa(t_list **stack_b, t_list **stack_a)
{
	if (push(stack_b, stack_a) == -1)
		return (-1);
	ft_putendl_fd("pa", 1);
	return (0);
}

int	pb(t_list **stack_a, t_list **stack_b)
{
	if (push(stack_a, stack_b) == -1)
		return (-1);
	ft_putendl_fd("pb", 1);
	return (0);
}
