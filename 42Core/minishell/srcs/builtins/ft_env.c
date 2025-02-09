/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:46:17 by jsarda            #+#    #+#             */
/*   Updated: 2024/07/22 15:03:53 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_data *data, t_shell *shell, char **args)
{
	(void)args;
	if (!shell->envp)
		return ;
	print_env(shell->envp, data);
	g_return_satus = 0;
}
