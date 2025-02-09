/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_count_operators.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <jtaravel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:10:43 by jtaravel          #+#    #+#             */
/*   Updated: 2024/07/10 16:39:42 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_hd_operator(char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<')
			c++;
		i++;
	}
	return (c);
}

int	count_in_operator(char *str, int i)
{
	int	c;

	c = 0;
	if (i == 0)
	{
		if (str[i] == '<' && str[i + 1] != '<')
			c++;
	}
	else
	{
		if (str[i] == '<' && str[i + 1] != '<' && str[i - 1] != '<')
			c++;
	}
	return (c);
}

int	count_out_operator(char *str, int i)
{
	int	c;

	c = 0;
	if (i == 0)
	{
		if (str[i] == '>' && str[i + 1] != '>')
			c++;
		if (str[i] == '>' && str[i + 1] == '>')
			c++;
	}
	else
	{
		if (str[i] == '>' && str[i + 1] != '>' && str[i - 1] != '>')
			c++;
		if (str[i] == '>' && str[i + 1] == '>' && str[i - 1] != '>')
			c++;
	}
	return (c);
}

int	count_redir_operator(char *str, int mode)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		if (mode == 1)
			c += count_in_operator(str, i);
		else
			c += count_out_operator(str, i);
		i++;
	}
	return (c);
}

int	count_operators(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '|' || input[i] == '<' || input[i] == '>'
			|| (input[i] == '<' && input[i + 1] == '<')
			|| (input[i] == '>' && input[i + 1] == '>'))
			count++;
		i++;
	}
	return (count);
}
