/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_block.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <jtaravel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:56:03 by jtaravel          #+#    #+#             */
/*   Updated: 2024/07/17 16:14:02 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*parse_block(char *str, t_data *datas, t_shell *shell, int flag)
{
	int		i;
	char	**split;
	char	*tmp_str;

	tmp_str = NULL;
	split = ft_split_quotes(str, ' ');
	tmp_str = ft_recreate_input(str, split, tmp_str, shell);
	if (!init_redir_arrays(datas, tmp_str))
		return (NULL);
	i = -1;
	while (split[++i])
	{
		flag = cut_parse_block_loop_1(split, i, datas, shell);
		if (flag == 0)
			flag = cut_parse_block_loop_2(split, i, datas, shell);
		if (flag == 1)
		{
			split = erase_split_parse_block(split, shell, tmp_str, &i);
			if (!split)
				return (freetab(datas->limiter_hd), freetab(datas->namein),
					freetab(datas->nameout), NULL);
			continue ;
		}
	}
	return (end_init_one_block(datas, split, tmp_str, shell));
}

t_data	*end_init_one_block(t_data *datas, char **tab, char *s, t_shell *shell)
{
	int	i;

	if (datas->limiter_hd)
		datas->limiter_hd[datas->nb_hd] = 0;
	if (datas->namein)
		datas->namein[datas->nb_in] = 0;
	if (datas->nameout)
		datas->nameout[datas->nb_out] = 0;
	datas->args = malloc(sizeof(char *) * (ft_tablen(tab) + 1));
	i = -1;
	while (tab[++i])
		datas->args[i] = ft_strdup(tab[i]);
	datas->args[i] = 0;
	i = -1;
	while (datas->args[++i])
	{
		datas->args[i] = expander(datas->args[i], &shell->envp, 0, NULL);
		datas->args[i] = delete_extra_quotes(datas->args[i], 0, 0, 0);
	}
	datas->cmd = ft_strdup(datas->args[0]);
	freetab(tab);
	free(s);
	return (datas);
}
