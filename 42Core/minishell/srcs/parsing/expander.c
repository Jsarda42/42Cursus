/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:44:22 by jtaravel          #+#    #+#             */
/*   Updated: 2024/07/25 14:31:29 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cut_expander_loop_1(char *recup, char *res, t_env **env, int *f)
{
	char	*tmp_content;
	char	*tmp_res;

	tmp_content = NULL;
	tmp_res = NULL;
	if (!res)
	{
		res = malloc(1);
		res[0] = 0;
	}
	tmp_content = get_content_env(env, recup);
	tmp_res = ft_strjoin(res, tmp_content);
	free(tmp_content);
	free(res);
	res = ft_strdup(tmp_res);
	free(tmp_res);
	free(recup);
	recup = NULL;
	*f = 1;
	return (res);
}

static	char	*expander_loop_init(int *f, int *i)
{
	*i = -1;
	*f = 0;
	return (NULL);
}

char	*cut_expander_in_loop(char *str, int *i, char *recup)
{
	while (str && str[*i] && str[*i] != ' '
		&& valid_name(str[*i]) && str[*i] != '$')
		recup = reallocator(recup, str[(*i)++], 0);
	if (str[*i] == '$' || str[*i] == ' ' || !valid_name(str[*i]))
		(*i)--;
	return (recup);
}

char	*cut_expander_while_loop(char *str, t_env **env, int dq, int sq)
{
	int		f;
	int		i;
	char	*recup;
	char	*res;

	res = expander_loop_init(&f, &i);
	while (str && str[++i])
	{
		recup = recup_dq_sq_expander(str, i, &sq, &dq);
		if (str[i] == '$' && sq == 0 && ++i)
		{
			recup = cut_expander_in_loop(str, &i, recup);
			if (recup)
				res = cut_expander_loop_1(recup, res, env, &f);
		}
		else
		{
			f = 1;
			res = reallocator(res, str[i], 0);
		}
		if (!recup && f == 0)
			res = reallocator(res, str[i], 0);
		f = 0;
	}
	return (res);
}

char	*expander(char *str, t_env **env, int i, char *res)
{
	(void)i;
	(void)res;
	if (!str || !str[0])
		return (str);
	res = cut_expander_while_loop(str, env, 0, 0);
	free(str);
	if (res == NULL)
	{
		free(res);
		res = ft_strdup("");
	}
	return (res);
}
