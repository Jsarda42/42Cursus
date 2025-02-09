/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:13:55 by jsarda            #+#    #+#             */
/*   Updated: 2024/07/25 13:37:53 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	last_child(t_shell *shell, t_data *data, char **env)
{
	data->fdin = shell->pipes[0];
	handle_redir(shell, data);
	manage_sig();
	if (data->cmd && is_built_in(data) == -1)
	{
		if (data->fdin != -1 && data->fdin != 0)
		{
			if (dup2(data->fdin, STDIN_FILENO) == -1)
				perror("dup2");
			close(data->fdin);
		}
		if (data->fdout != -1 && data->fdout != 1)
		{
			dup2(data->fdout, STDOUT_FILENO);
			close(data->fdout);
		}
		env = create_char_env(shell->envp, get_env_list_size(shell->envp));
		if (execve(data->path, data->args, env) == -1)
			execve_fail();
	}
	if (is_built_in(data) != -1)
		exec_built_in(data, shell);
	close(shell->pipes[1]);
	close(data->fdout);
	exit_other_child(data, shell);
}

void	last_exec(t_shell *shell, t_data *data)
{
	char	**env;

	env = NULL;
	data->pid = fork();
	if (data->pid == 0)
		last_child(shell, data, env);
	close(shell->pipes[0]);
	close(shell->pipes[1]);
	close_fd(data);
}
