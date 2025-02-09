/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_block_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <jtaravel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:57:53 by jtaravel          #+#    #+#             */
/*   Updated: 2024/07/23 13:42:56 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**erase_split_parse_block(char **split, t_shell *shell, char *s, int *i)
{
	if (!split[*i + 1])
		return (ft_errors_parsing(0,
				"syntax error near unexpected token `newline'\n",
				shell, NULL), freetab(split), free(s), NULL);
	split = ft_erase_in_tab(split, *i, *i + 1);
	*i = -1;
	return (split);
}

t_data	*pre_init_block(void)
{
	t_data	*tmp;

	tmp = malloc(sizeof(struct s_data));
	if (!tmp)
		return (NULL);
	tmp->cmd = NULL;
	tmp->path = NULL;
	tmp->args = NULL;
	tmp->redir_type_in = 0;
	tmp->redir_type_out = 0;
	tmp->fdin = 0;
	tmp->fdintmp = 0;
	tmp->fdout = 1;
	tmp->namein = NULL;
	tmp->nameout = NULL;
	tmp->is_hd = 0;
	tmp->limiter_hd = NULL;
	tmp->tmpfile_hd = NULL;
	tmp->nb_hd = 0;
	tmp->nb_in = 0;
	tmp->nb_out = 0;
	tmp->status = 0;
	tmp->pid = -42;
	tmp->next = NULL;
	return (tmp);
}

t_data	*ft_lstlast_block(t_data *lst)
{
	t_data	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
	}
	return (tmp);
}

int	block_add_back(t_data **alst, t_data *new)
{
	t_data	*tmp;

	tmp = *alst;
	if (!new)
		return (1);
	if ((*alst))
	{
		tmp = ft_lstlast_block(*alst);
		tmp->next = new;
	}
	else
		*alst = new;
	return (0);
}

int	init_redir_arrays(t_data *datas, char *tmp_str)
{
	int	nb_redir_in;
	int	nb_redir_out;
	int	nb_hd;

	if (!tmp_str)
		return (0);
	nb_redir_in = count_redir_operator(tmp_str, 1);
	nb_redir_out = count_redir_operator(tmp_str, 0);
	nb_hd = count_hd_operator(tmp_str);
	if (nb_hd)
		datas->limiter_hd = malloc(sizeof(char *) * (nb_hd + 1));
	if (nb_redir_in)
		datas->namein = malloc(sizeof(char *) * (nb_redir_in + 1));
	if (nb_redir_out)
		datas->nameout = malloc(sizeof(char *) * (nb_redir_out + 1));
	return (1);
}
