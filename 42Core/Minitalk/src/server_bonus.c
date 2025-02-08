/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:50:39 by jsarda            #+#    #+#             */
/*   Updated: 2024/02/05 15:55:28 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

#define BUFFER_SIZE 100

void	add_bit_to_string(int bit, char **str, int *str_size, int *str_capacity)
{
	if (*str_size == *str_capacity)
	{
		*str_capacity += BUFFER_SIZE;
		*str = ft_realloc(*str, *str_capacity);
		if (!(*str))
		{
			free(*str);
			exit(EXIT_FAILURE);
		}
	}
	(*str)[*str_size] = bit;
	(*str_size)++;
}

void	print_string(char *str)
{
	ft_printf("%s", str);
	free(str);
	str = NULL;
}

void	sig_handler(int sig, siginfo_t *info, void *context)
{
	static int	bit;
	static int	i;
	static char	*str = NULL;
	static int	str_size = 0;
	static int	str_capacity = 0;

	(void)context;
	if (sig == SIGUSR1)
		i |= (0b00000001 << bit);
	bit++;
	if (bit == 8)
	{
		add_bit_to_string(i, &str, &str_size, &str_capacity);
		bit = 0;
		i = 0;
	}
	if (str_size > 0 && str[str_size - 1] == '\0')
	{
		print_string(str);
		str_size = 0;
		str_capacity = 0;
		kill(info->si_pid, SIGUSR1);
	}
	kill(info->si_pid, SIGUSR2);
}

int	main(int argc, char **argv)
{
	int					pid;
	struct sigaction	sa;

	(void)argv;
	if (argc != 1)
	{
		ft_printf("\033[91mError: wrong format.\033[0m\n");
		ft_printf("\033[33mTry: ./server\033[0m\n");
		return (0);
	}
	pid = getpid();
	ft_printf("\033[94mPID\033[0m \033[96m->\033[0m %d\n", pid);
	ft_printf("\033[90mWaiting for a message...\033[0m\n");
	sa.sa_sigaction = sig_handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (argc == 1)
		pause();
	return (0);
}
