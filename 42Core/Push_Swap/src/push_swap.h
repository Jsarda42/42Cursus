/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 10:36:33 by jsarda            #+#    #+#             */
/*   Updated: 2024/01/26 10:47:30 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# ifndef DEBUGG
#  define DEBUG 0
# endif

# include "../libft/libft.h"
# include <limits.h>

typedef struct s_list
{
	int				data;
	int				index;
	int				pos_a;
	int				pos_b;
	struct s_list	*next;
	struct s_list	*target;
}					t_list;

typedef enum s_bool
{
	false = 0,
	true = 1
}					t_bool;

// rules functions
int					sa(t_list **stack_a);
int					sb(t_list **stack_b);
int					pa(t_list **stack_b, t_list **stack_a);
int					pb(t_list **stack_a, t_list **stack_b);
int					ra(t_list **stack);
int					rb(t_list **stack);
int					rr(t_list **stack_a, t_list **stack_b);
int					rra(t_list **stack_a);
int					rrb(t_list **stack_b);
int					rrr(t_list **stack_a, t_list **stack_b);

// lst utils functions
int					ft_lstsize(t_list *stack);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstadd_front(t_list **lst, t_list *new);
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstnew(int value);

// utils
void				error_message(char *message, t_list **stack);
t_bool				args_parsing(char **argv);
t_bool				is_sorted(t_list *stack_a);
t_list				*get_target(int current_a_data, t_list **stack_b);
t_bool				way_to_move(t_list **stack, int current_node_pos);
t_list				*get_min_target(t_list *stack);
t_list				*get_target_closest_bigger(int current_a_data,
						t_list **stack);
int					get_max(t_list *stack);
int					get_min(t_list *stack);
int					get_median(t_list **stack);
int					get_node_position(t_list *stack, t_list *current_node);
t_bool				is_duplicate(char **argv);
t_bool				is_valid_int(char *arg);

// cost
t_list				*cheapest_node(t_list **stack_a, t_list **stack_b);

// free function
void				clear_list(t_list **stack);
void				ft_free(char **str);
void				free_stack(t_list **stack_a, t_list **stack_b);
void				free_args(int argc, t_list **stack, char **args,
						char *message);

// sort function
void				sort_3(t_list **stack_a);
void				sort(t_list **stack_a, t_list **stack_b);

// both rotation
void				both_rotate_reverse(t_list **stack_a, t_list **stack_b,
						t_list *cheapest);
void				normal_rotation(t_list **stack_a, t_list **stack_b);
void				both_rotate(t_list **stack_a, t_list **stack_b,
						t_list *cheapest);
// push to stack
void				push_best_to_b(t_list **stack_a, t_list **stack_b);
void				push_back_to_a(t_list **stack_a, t_list **stack_b);

#endif
