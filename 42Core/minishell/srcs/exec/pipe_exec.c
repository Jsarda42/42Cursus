/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:15:58 by jsarda            #+#    #+#             */
/*   Updated: 2024/07/25 13:42:11 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first(t_data *head, t_shell *shell)
{
	head->path = get_cmd_path(head, shell);
	if (!head->path && head->cmd && is_built_in(head) == -1)
		manage_no_path(head, shell, 1);
	else if (!head->path && !head->cmd && is_built_in(head) == -1)
	{
		if (head->fdin != 0 && head->fdin != -1)
			close(head->fdin);
		return ;
	}
	else
		first_exec(shell, head, head->path);
}

void	mid(t_data *head, t_shell *shell)
{
	head->path = get_cmd_path(head, shell);
	if (!head->path && head->cmd && is_built_in(head) == -1)
		manage_no_path(head, shell, 1);
	else if (!head->path && !head->cmd && is_built_in(head) == -1)
	{
		if (head->fdin != 0 && head->fdin != -1)
			close(head->fdin);
		return ;
	}
	else
		middle_exec(shell, head, shell->pipes[0]);
}

void	last(t_data *head, t_shell *shell)
{
	head->path = get_cmd_path(head, shell);
	if (!head->path && head->cmd && is_built_in(head) == -1)
		manage_no_path(head, shell, 1);
	else if (!head->path && !head->cmd && is_built_in(head) == -1)
	{
		if (head->fdin != 0 && head->fdin != -1)
			close(head->fdin);
		return ;
	}
	else
		last_exec(shell, head);
}

void	exec_pipe(t_shell *shell, int num_cmd)
{
	int		i;
	t_data	*head;

	head = shell->datas;
	i = -1;
	pipe(shell->pipes);
	if (head->fdintmp != -1 && head->cmd)
		first(head, shell);
	else
		close(shell->pipes[1]);
	head = head->next;
	while (++i < (num_cmd - 2))
	{
		mid(head, shell);
		head = head->next;
	}
	last(head, shell);
	head = shell->datas;
	ft_wait(head);
	close(shell->pipes[1]);
	close(shell->pipes[0]);
}
