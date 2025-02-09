/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_add_spaces.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <jtaravel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:37:21 by jtaravel          #+#    #+#             */
/*   Updated: 2024/07/22 17:12:42 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_in_quotes(char *str, int i, int j)
{
	int	sq;
	int	dq;

	sq = 0;
	dq = 0;
	while (str && str[i] && i < j)
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

char	*add_space_loop(char *res, char *input, int i, int j)
{
	while (input[i])
	{
		if (((input[i] == '<' && input[i + 1] == '<')
				|| (input[i] == '>' && input[i + 1] == '>'))
			&& check_if_in_quotes(input, 0, i) == 0)
		{
			res[j++] = ' ';
			res[j++] = input[i++];
			res[j++] = input[i];
			res[j] = ' ';
		}
		else if ((input[i] == '|' || input[i] == '<' || input[i] == '>')
			&& check_if_in_quotes(input, 0, i) == 0)
		{
			res[j++] = ' ';
			res[j++] = input[i];
			res[j] = ' ';
		}
		else
			res[j] = input[i];
		j++;
		i++;
	}
	res[j] = 0;
	return (res);
}

char	*add_space(char *input)
{
	char	*res;
	int		count;

	count = count_operators(input);
	if (count == 0)
		return (input);
	res = malloc(sizeof(char) * (ft_strlen(input) + (count * 2) + 1));
	if (!res)
		return (NULL);
	ft_bzero(res, ft_strlen(input) + (count * 2) + 1);
	res = add_space_loop(res, input, 0, 0);
	free(input);
	return (res);
}
