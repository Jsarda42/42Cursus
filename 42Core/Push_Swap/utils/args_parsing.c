/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 10:17:07 by jsarda            #+#    #+#             */
/*   Updated: 2024/01/26 10:06:54 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/push_swap.h"

int	ft_issign(int c)
{
	return (c == 43 || c == 45);
}

int	ft_issign_or_space(int c)
{
	return (c == 43 || c == 45 || (c >= 9 && c <= 13) || c == 32);
}

static int	ft_isspace(int c)
{
	return (c == 32 || c == 9);
}

t_bool	is_duplicate(char **argv)
{
	int	i;
	int	j;
	int	num_i;
	int	num_j;

	i = -1;
	while (argv[++i])
	{
		if (is_valid_int(argv[i]))
		{
			num_i = ft_atocoi(argv[i]);
			j = i + 1;
			while (argv[j])
			{
				if (is_valid_int(argv[j]))
				{
					num_j = ft_atocoi(argv[j]);
					if (num_i == num_j)
						return (true);
				}
				j++;
			}
		}
	}
	return (false);
}

t_bool	args_parsing(char **argv)
{
	int	i;
	int	j;
	int	space;

	{
		i = 0;
		while (argv[++i])
		{
			j = -1;
			space = 0;
			while (argv[i][++j])
			{
				if (ft_issign_or_space(argv[i][j]))
					space++;
				if ((!ft_isdigit(argv[i][j]) && !ft_issign_or_space(argv[i][j]))
					|| (ft_isdigit(argv[i][j]) && ft_issign(argv[i][j + 1]))
					|| (ft_issign(argv[i][j]) && ft_issign(argv[i][j + 1]))
					|| (ft_issign(argv[i][j]) && ft_isspace(argv[i][j + 1])))
					return (false);
			}
			if (space == j)
				return (false);
		}
	}
	return (true);
}
