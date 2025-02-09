/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:02:58 by jtaravel          #+#    #+#             */
/*   Updated: 2024/07/22 16:57:12 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstlast_env(t_env *lst)
{
	t_env	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
	}
	return (tmp);
}

t_env	*ft_lstnew_env(char *line, char *name, char *value)
{
	t_env	*tmp;

	tmp = malloc(sizeof(struct s_env));
	if (!tmp)
		return (0);
	tmp->line = ft_strdup(line);
	tmp->name = ft_strdup(name);
	tmp->value = ft_strdup(value);
	tmp->next = NULL;
	return (tmp);
}

void	ft_lstadd_back_env(t_env **alst, t_env *new)
{
	t_env	*tmp;

	tmp = *alst;
	if ((*alst))
	{
		tmp = ft_lstlast_env(*alst);
		tmp->next = new;
	}
	else
	{
		*alst = new;
	}
}

int	little_env(t_env **env)
{
	char	**new_env;
	char	**split;
	int		i;
	char	cwd[PATH_MAX];

	new_env = malloc(sizeof(char *) * 4);
	if (!new_env)
		return (1);
	new_env[0] = ft_strjoin("PWD=", getcwd(cwd, PATH_MAX));
	new_env[1] = ft_strdup("SHLVL=1");
	i = 0;
	while (new_env[i])
	{
		split = ft_split(new_env[i], '=');
		if (!split || !split[0] || !split[1])
			return (freetab(split), 0);
		ft_lstadd_back_env(env, ft_lstnew_env(new_env[i], split[0], split[1]));
		freetab(split);
		split = NULL;
		i++;
	}
	return (0);
}

int	env_init(t_env **env, char **envp)
{
	int		i;
	char	**split;

	*env = NULL;
	i = 0;
	if (!envp[i])
	{
		if (little_env(env))
			return (1);
		return (0);
	}
	while (envp[i])
	{
		split = ft_split(envp[i], '=');
		if (!split || !split[0] || !split[1])
			return (freetab(split), 0);
		ft_lstadd_back_env(env, ft_lstnew_env(envp[i], split[0], split[1]));
		freetab(split);
		split = NULL;
		i++;
	}
	return (0);
}
