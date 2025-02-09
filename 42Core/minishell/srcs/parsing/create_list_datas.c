/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_datas.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:16:18 by jtaravel          #+#    #+#             */
/*   Updated: 2024/07/22 10:50:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	{
		*alst = new;
	}
	return (0);
}

int	create_list(char *input, t_data **datas, t_shell *shell)
{
	char	**split;
	int		i;
	t_data	*tmp_data;

	*datas = NULL;
	split = ft_split_quotes(input, '|');
	if (!split || !split[0])
		return (freetab(split), 0);
	i = 0;
	while (split[i])
	{
		tmp_data = pre_init_block();
		if (block_add_back(datas, parse_block(ft_strdup(split[i]),
					tmp_data, shell)))
			return (free(tmp_data), free(input), freetab(split), 1);
		i++;
	}
	freetab(split);
	return (0);
}
