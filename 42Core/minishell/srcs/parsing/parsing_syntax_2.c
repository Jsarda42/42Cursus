/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_syntax_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <jtaravel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:09:53 by jtaravel          #+#    #+#             */
/*   Updated: 2024/07/23 13:29:12 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	recup_second_quote(char *str, int i, int mode)
{
	if (mode == 1)
	{
		while (str[i])
		{
			if (str[i] == '"')
				return (i);
			i++;
		}
	}
	else if (mode == 2)
	{
		while (str[i])
		{
			if (str[i] == '\'')
				return (i);
			i++;
		}
	}
	return (-1);
}

int	open_file_loop(t_data *tmp_data, int i, int fd)
{
	i = 0;
	while (tmp_data->namein && tmp_data->namein[i])
	{
		tmp_data->fdintmp = open(tmp_data->namein[i], O_RDONLY, 0644);
		if (tmp_data->fdintmp == -1)
			return (ft_errors_parsing(1, strerror(errno),
					NULL, tmp_data->namein[i]), 2);
		close(tmp_data->fdintmp);
		i++;
	}
	i = 0;
	while (tmp_data->nameout && tmp_data->nameout[i])
	{
		fd = open(tmp_data->nameout[i], O_WRONLY | O_CREAT, 0644);
		if (fd == -1)
			return (ft_errors_parsing(1, strerror(errno),
					NULL, tmp_data->nameout[i]), 2);
		close(fd);
		i++;
	}
	return (0);
}

int	open_files(t_data **datas)
{
	t_data	*tmp_data;

	tmp_data = *datas;
	while (tmp_data)
	{
		if (open_file_loop(tmp_data, 0, -1))
			return (2);
		tmp_data = tmp_data->next;
	}
	return (0);
}
