/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:15:57 by jsarda            #+#    #+#             */
/*   Updated: 2024/01/26 09:38:57 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/push_swap.h"

void	clear_list(t_list **stack)
{
	t_list	*current;
	t_list	*next_node;

	current = *stack;
	while (current)
	{
		next_node = current->next;
		free(current);
		current = next_node;
	}
	*stack = NULL;
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_stack(t_list **stack_a, t_list **stack_b)
{
	t_list	*head;
	t_list	*tmp;

	head = *stack_a;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
	free(stack_a);
	head = *stack_b;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
	free(stack_b);
}

void	free_args(int argc, t_list **stack, char **args, char *message)
{
	if (argc == 2)
		ft_free(args);
	error_message(message, stack);
}
