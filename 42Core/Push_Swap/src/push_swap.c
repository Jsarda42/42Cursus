/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 13:17:35 by jsarda            #+#    #+#             */
/*   Updated: 2024/01/26 12:28:16 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static char	**split_and_join(char **argv, char *tmp)
{
	char	**args;
	int		j;

	j = 1;
	args = argv;
	while (args[++j])
	{
		if (argv[j][0] == '\0')
			return (free(tmp), NULL);
		tmp = ft_strjoin(tmp, args[j]);
		if (!tmp)
			return (free(tmp), NULL);
	}
	args = ft_split(tmp, ' ');
	free(tmp);
	return (args);
}

static char	**init_stack(t_list **stack, char **argv)
{
	t_list	*new;
	char	**args;
	int		i;
	char	*tmp;
	int		j;

	i = 0;
	args = argv;
	tmp = ft_strdup(args[1]);
	if (!tmp)
		return (0);
	j = 1;
	args = split_and_join(args, tmp);
	if (!args)
		return (ft_free(args), NULL);
	*stack = ft_lstnew(ft_atocoi(args[0]));
	while (args[++i])
	{
		new = ft_lstnew(ft_atocoi(args[i]));
		ft_lstadd_back(stack, new);
	}
	return (args);
}

static void	init_sort(char **argv, t_list **stack_a, t_list **stack_b)
{
	if (is_duplicate(argv))
	{
		ft_free(argv);
		free_stack(stack_a, stack_b);
		error_message("Error", NULL);
	}
	if (is_sorted(*stack_a))
	{
		clear_list(stack_a);
		clear_list(stack_b);
	}
	else
		sort(stack_a, stack_b);
}

void	main_error(t_list **stack_a, t_list **stack_b)
{
	free_stack(stack_a, stack_b);
	error_message("Error", NULL);
}

int	main(int argc, char **argv)
{
	t_list	**stack_a;
	t_list	**stack_b;
	int		j;

	j = 0;
	while (++j < argc)
		if (!is_valid_int(argv[j]))
			error_message("Error", NULL);
	stack_a = (t_list **)malloc(sizeof(t_list));
	stack_b = (t_list **)malloc(sizeof(t_list));
	*stack_a = NULL;
	*stack_b = NULL;
	if (argc >= 2)
	{
		if (!args_parsing(argv))
			main_error(stack_a, stack_b);
		argv = init_stack(stack_a, argv);
		if (!argv)
			main_error(stack_a, stack_b);
		init_sort(argv, stack_a, stack_b);
		ft_free(argv);
	}
	free_stack(stack_a, stack_b);
	return (0);
}
