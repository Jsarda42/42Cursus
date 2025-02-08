/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:58:57 by jsarda            #+#    #+#             */
/*   Updated: 2024/04/01 10:24:36 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo			philo[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];
	t_prog			prog;

	if (argc != 5 && argc != 6)
		error_exit("The arguments must be 5 or 6");
	parsing_init(philo, argc, argv);
	init_all(&prog, philo, forks);
	ft_threads(philo);
	destory_all(philo, forks);
	return (0);
}
