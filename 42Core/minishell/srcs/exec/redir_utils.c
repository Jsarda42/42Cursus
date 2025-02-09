/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <jtaravel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 22:12:43 by juliensarda       #+#    #+#             */
/*   Updated: 2024/07/23 14:02:53 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	readline_loop(t_data *data, t_shell *shell, char *eof, int fd)
{
	char	*buf;

	(void)shell;
	(void)data;
	while (1)
	{
		buf = readline("> ");
		if (!buf)
			break ;
		if (buf && !ft_strcmp(eof, buf))
		{
			free(buf);
			break ;
		}
		if (buf)
		{
			ft_putendl_fd(buf, fd);
			free(buf);
		}
	}
}

void	ft_wait_hd(t_data *data)
{
	int	status;

	waitpid(data->pid, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status) + 128;
	g_return_satus = status;
	if (g_return_satus == 130)
		printf("\n");
}
