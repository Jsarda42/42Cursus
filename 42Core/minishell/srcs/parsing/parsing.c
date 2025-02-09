/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <jtaravel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:09:42 by jtaravel          #+#    #+#             */
/*   Updated: 2024/07/22 17:08:00 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_recreate_input(char *str, char **tab, char *s, t_shell *shell)
{
	int	k;

	if (!tab)
		return (freetab(tab), free(str), NULL);
	free(str);
	s = malloc(1);
	s[0] = '\0';
	k = -1;
	while (tab[++k])
	{
		str = ft_strjoin(s, tab[k]);
		free(s);
		s = ft_strjoin(str, " ");
		free(str);
	}
	if (check_syntaxes(s))
		return (free(s), freetab(tab),
			ft_errors_parsing(0, "syntax error\n", shell, NULL), NULL);
	return (s);
}

int	create_list(char *input, t_data **datas, t_shell *shell)
{
	char	**split;
	int		i;
	t_data	*tmp_data;

	*datas = NULL;
	split = ft_split_quotes(input, '|');
	if (!split || !split[0])
		return (freetab(split), 2);
	i = 0;
	while (split[i])
	{
		tmp_data = pre_init_block();
		if (!tmp_data)
		{
			printf("%s\n", strerror(errno));
			return (free(tmp_data), freetab(split), 1);
		}
		if (block_add_back(datas, parse_block(ft_strdup(split[i]),
					tmp_data, shell, 0)))
			return (free(tmp_data), freetab(split), 1);
		i++;
	}
	freetab(split);
	return (0);
}

char	*clear_first_space(char *input)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	while (input[i] && is_white_space(input[i]))
		i++;
	res = malloc(sizeof(char) * (ft_strlen(input) - i + 1));
	if (!res)
		return (NULL);
	j = 0;
	while (input[i])
	{
		res[j] = input[i];
		j++;
		i++;
	}
	res[j] = 0;
	if (ft_strlen(res) == 0)
		return (free(input), free(res), NULL);
	free(input);
	return (res);
}

char	*replace_shit(char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (is_white_space(input[i]))
			input[i] = 32;
		i++;
	}
	return (input);
}

int	parse_input(char *input, t_shell *shell)
{
	input = replace_shit(input);
	input = clear_first_space(input);
	if (!input)
		return (4);
	if (check_valid_quotes(input))
		return (ft_errors_parsing(0, "syntax error near unexpected token\n",
				shell, NULL), free(input), 4);
	input = add_space(input);
	if (!input)
		return (1);
	if (create_list(input, &(shell->datas), shell))
		return (ft_clear_datas(&(shell->datas)), free(input), 3);
	if (DEBUG)
		debug_print_block(&(shell->datas));
	free(input);
	return (0);
}
