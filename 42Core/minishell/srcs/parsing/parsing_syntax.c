/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_syntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:08:36 by jtaravel          #+#    #+#             */
/*   Updated: 2024/07/25 14:20:34 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_valid_quotes(char *str)
{
	int	i;
	int	sq;
	int	dq;

	i = 0;
	sq = 0;
	dq = 0;
	while (str[i])
	{
		if (str[i] == '"' && dq == 0 && sq == 0)
			dq = 1;
		else if (str[i] == '\'' && sq == 0 && dq == 0)
			sq = 1;
		else if (str[i] == '"' && dq == 1 && sq == 0)
			dq = 0;
		else if (str[i] == '\'' && sq == 1 && dq == 0)
			sq = 0;
		i++;
	}
	if (sq || dq)
		return (1);
	return (0);
}

int	check_syntaxes(char *str)
{
	if (str == NULL || ft_strncmp(str, " ", ft_strlen(str)) == 0)
		return (1);
	if (check_valid_quotes(str))
		return (1);
	return (0);
}

char	*delete_extra_quotes(char *str, int i, int dq, int sq)
{
	int	pos1;
	int	pos2;

	while (str && str[i])
	{
		pos1 = 0;
		pos2 = -1;
		pos1 = cut_delete_quote_loop(str, i, &dq, &sq);
		if (dq == 1 && sq == 0)
			pos2 = recup_second_quote(str, i + 1, 1);
		if (sq == 1 && dq == 0)
			pos2 = recup_second_quote(str, i + 1, 2);
		if (pos2 != -1)
		{
			str = cut_delete_quote(str, pos1, pos2);
			if (!str)
				return (NULL);
			sq = 0;
			dq = 0;
			i = pos2 - 2;
		}
		i++;
	}
	return (str);
}

char	*cut_delete_quote(char *str, int pos1, int pos2)
{
	if (pos2 == -1)
		return (NULL);
	else
	{
		str = ft_erase(str, pos1, 1);
		str = ft_erase(str, pos2 - 1, 1);
	}
	return (str);
}

int	cut_delete_quote_loop(char *str, int i, int *dq, int *sq)
{
	if (str[i] == '\'' && *sq == 0 && *dq == 0)
	{
		*sq = 1;
		return (i);
	}
	else if (str[i] == '\"' && *dq == 0 && *sq == 0)
	{
		*dq = 1;
		return (i);
	}
	return (0);
}
