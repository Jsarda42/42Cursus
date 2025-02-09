/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_block_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <jtaravel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:07:55 by jtaravel          #+#    #+#             */
/*   Updated: 2024/07/17 11:32:55 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ccut_parse_block_loop_1(char **split, int i, t_data *datas, t_shell *shell)
{
	if (!ft_strncmp(split[i], ">>", ft_strlen(split[i])) && i == 0)
	{
		datas->nameout[datas->nb_out++] = expander(ft_strdup(split[i + 1]),
				&shell->envp, 0, NULL);
		datas->redir_type_out = APPEND;
		return (1);
	}
	else if (!ft_strncmp(split[i], "<<", ft_strlen(split[i])) && i == 0)
	{
		datas->limiter_hd[datas->nb_hd++] = ft_strdup(split[1]);
		datas->redir_type_in = HD;
		datas->is_hd = 1;
		return (1);
	}
	return (0);
}

int	cut_parse_block_loop_1(char **split, int i, t_data *datas, t_shell *shell)
{
	if (!ft_strncmp(split[i], "<", ft_strlen(split[i])) && i == 0)
	{
		datas->namein[datas->nb_in++] = expander(ft_strdup(split[i + 1]),
				&shell->envp, 0, NULL);
		datas->redir_type_in = IN;
		return (1);
	}
	else if (!ft_strncmp(split[i], ">", ft_strlen(split[i])) && i == 0)
	{
		datas->nameout[datas->nb_out++] = expander(ft_strdup(split[i + 1]),
				&shell->envp, 0, NULL);
		datas->redir_type_out = OUT;
		return (1);
	}
	else
	{
		return (ccut_parse_block_loop_1(split, i, datas, shell));
	}
	return (0);
}

int	ccut_parse_block_loop_2(char **split, int i, t_data *datas, t_shell *shell)
{
	if (!ft_strncmp(split[i], ">>", ft_strlen(split[i])))
	{
		datas->nameout[datas->nb_out++] = expander(ft_strdup(split[i + 1]),
				&shell->envp, 0, NULL);
		datas->redir_type_out = APPEND;
		return (1);
	}
	else if (!ft_strncmp(split[i], "<<", ft_strlen(split[i])))
	{
		datas->limiter_hd[datas->nb_hd++] = ft_strdup(split[i + 1]);
		datas->redir_type_in = HD;
		datas->is_hd = 1;
		return (1);
	}
	return (0);
}

int	cut_parse_block_loop_2(char **split, int i, t_data *datas, t_shell *shell)
{
	if (!ft_strncmp(split[i], "<", ft_strlen(split[i])))
	{
		datas->namein[datas->nb_in++] = expander(ft_strdup(split[i + 1]),
				&shell->envp, 0, NULL);
		datas->redir_type_in = IN;
		return (1);
	}
	else if (!ft_strncmp(split[i], ">", ft_strlen(split[i])))
	{
		datas->nameout[datas->nb_out++] = expander(ft_strdup(split[i + 1]),
				&shell->envp, 0, NULL);
		datas->redir_type_out = OUT;
		return (1);
	}
	else
		return (ccut_parse_block_loop_2(split, i, datas, shell));
	return (0);
}
