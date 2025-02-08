/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:50:08 by jsarda            #+#    #+#             */
/*   Updated: 2024/02/05 13:50:10 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int			g_received = 0;

static void	ft_confirm(int signal)
{
	if (signal == SIGUSR2)
		g_received = 1;
	else
		ft_printf("\033[32mReceived.\033[0m\n");
}

void	send_bits(int pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		g_received = 0;
		if ((c & (0b00000001 << bit)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (g_received == 0)
			usleep(100);
		bit++;
	}
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	i = 0;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		signal(SIGUSR1, ft_confirm);
		signal(SIGUSR2, ft_confirm);
		while (argv[2][i])
		{
			send_bits(pid, argv[2][i]);
			i++;
		}
		send_bits(pid, '\0');
		send_bits(pid, '\n');
	}
	else
	{
		ft_printf("\033[91mError: wrong format.\033[0m\n");
		ft_printf("\033[32mTry: ./client <PID> <MESSAGE>\033[0m\n");
		return (1);
	}
	return (0);
}
