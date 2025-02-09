/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <jtaravel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:42:51 by jtaravel          #+#    #+#             */
/*   Updated: 2024/07/17 11:47:51 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_first_part_loop(t_data *datas)
{
	int	j;

	j = -1;
	printf("\tcmd = %s\n", datas->cmd);
	printf("\targs:\n");
	while (datas->args[++j])
		printf("\t\targs[%d] = %s\n", j, datas->args[j]);
	printf("\tredir_type_in = %d\n", datas->redir_type_in);
	printf("\tredir_type_out = %d\n", datas->redir_type_out);
	printf("\tnamein:\n");
	j = 0;
	while (datas->namein && datas->namein[j])
	{
		printf("\t\tnamein[%d] = %s\n", j, datas->namein[j]);
		j++;
	}
	j = 0;
	printf("\tnameout:\n");
	while (datas->nameout && datas->nameout[j])
	{
		printf("\t\tnameout[%d] = %s\n", j, datas->nameout[j]);
		j++;
	}
}

void	debug_print_block(t_data **list)
{
	t_data	*datas;
	int		i;
	int		j;

	datas = *list;
	i = 0;
	while (datas)
	{
		printf("CMD %d\n", i);
		debug_first_part_loop(datas);
		printf("\tis_hd = %d\n", datas->is_hd);
		j = 0;
		printf("\tlimiters:\n");
		while (datas->limiter_hd && datas->limiter_hd[j])
		{
			printf("\t\tlimiters[%d] = %s\n", j, datas->limiter_hd[j]);
			j++;
		}
		datas = datas->next;
		i++;
	}
}
