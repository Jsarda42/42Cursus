/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:14:32 by jtaravel          #+#    #+#             */
/*   Updated: 2024/07/23 10:04:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_return_satus = 0;

void	sigint_handler(int sig)
{
	(void)sig;
	g_return_satus = 130;
	rl_on_new_line();
	printf("\n");
	rl_replace_line("", 1);
	rl_redisplay();
	return ;
}

int	loop_shell(t_shell *shell)
{
	char	*str;
	int		ret_parsing;

	ret_parsing = 0;
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sigint_handler);
		str = readline("ft_jsardashell$ ");
		if (!str)
			return (1);
		ret_parsing = parse_input(ft_strdup(str), shell);
		if (ret_parsing == 1)
			return (1);
		else if (ret_parsing == 2 || ret_parsing == 4)
			g_return_satus = 2;
		if (ret_parsing != 2 && ret_parsing != 3 && ret_parsing != 4)
			exec(shell);
		add_history(str);
		free(str);
		if (ret_parsing != 4)
			ft_clear_datas(&(shell->datas));
	}
	return (0);
}

void	init_shell(t_shell *shell, t_env *env, t_env *exp)
{
	shell->envp = env;
	shell->exp = exp;
}

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;
	t_env	*env;
	t_env	*exp;

	(void)ac;
	(void)av;
	if (!ttyname(1) || !ttyname(0))
		return (0);
	shell = malloc(sizeof(struct s_shell));
	if (!shell)
		return (1);
	if (env_init(&env, envp))
		return (free(shell), 1);
	if (env_init(&exp, envp))
		return (free(shell), 1);
	init_shell(shell, env, exp);
	loop_shell(shell);
	ft_free_env_list(&(shell->envp));
	ft_free_env_list(&(shell->exp));
	free(shell);
}
