/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <jtaravel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:19:28 by jtaravel          #+#    #+#             */
/*   Updated: 2024/07/22 17:15:11 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_content_env(t_env **env, char *find)
{
	t_env	*tmp;

	if (ft_strcmp(find, "?") == 0)
		return ((ft_itoa(g_return_satus)));
	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(find, tmp->name) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

int	valid_name(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| c == '_' || c == '?')
		return (1);
	return (0);
}

char	*reallocator(char *res, char c, int i)
{
	char	*cpy;

	cpy = NULL;
	if (!res)
	{
		res = malloc(2);
		res[0] = c;
		res[1] = 0;
		return (res);
	}
	if (res)
	{
		cpy = ft_strdup(res);
		free(res);
	}
	res = malloc(sizeof(char) * (ft_strlen(cpy) + 2));
	while (cpy && cpy[i])
	{
		res[i] = cpy[i];
		i++;
	}
	res[i] = c;
	res[i + 1] = 0;
	free(cpy);
	return (res);
}

char	*recup_dq_sq_expander(char *str, int i, int *sq, int *dq)
{
	if (str[i] == '\'' && *sq == 0 && *dq == 1)
		;
	else if (str[i] == '\'' && *sq == 0 && *dq == 0)
		*sq = 1;
	else if (str[i] == '\'' && *sq == 1)
		*sq = 0;
	else if (str[i] == '\"' && *dq == 0 && *sq == 1)
		;
	else if (str[i] == '\"' && *dq == 0 && *sq == 0)
		*dq = 1;
	else if (str[i] == '\"' && *dq == 1)
		*dq = 0;
	return (NULL);
}
