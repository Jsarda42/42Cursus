/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:57:42 by jsarda            #+#    #+#             */
/*   Updated: 2024/04/01 22:50:42 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_prog(t_prog *prog)
{
	prog->dead_flag = 0;
	safe_mutex(&prog->printf_lock, INIT);
	safe_mutex(&prog->dead_lock, INIT);
	safe_mutex(&prog->meal_lock, INIT);
}

void	philo_init(t_prog *prog, t_philo *philos, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < philos->num_of_philos)
	{
		philos[i].id = i + 1;
		philos[i].start_time = get_time_of_day();
		philos[i].num_of_philos = philos->num_of_philos;
		philos[i].philo_fork = &forks[i];
		philos[i].meal_eaten = 0;
		philos[i].last_meal = philos[i].start_time;
		philos[i].time_to_eat = philos->time_to_eat;
		philos[i].time_to_sleep = philos->time_to_sleep;
		philos[i].time_to_die = philos->time_to_die;
		philos[i].num_eat = philos->num_eat;
		philos[i].prog = prog;
		if (i == 0)
			philos[i].neighbor_fork = &forks[philos[i].num_of_philos - 1];
		else
			philos[i].neighbor_fork = &forks[i - 1];
		i++;
	}
}

void	init_forks(pthread_mutex_t *forks, int philo_num)
{
	int	i;

	i = 0;
	while (philo_num > i)
	{
		safe_mutex(&forks[i], INIT);
		i++;
	}
}

void	init_all(t_prog *prog, t_philo *philos, pthread_mutex_t *forks)
{
	init_prog(prog);
	init_forks(forks, philos->num_of_philos);
	philo_init(prog, philos, forks);
}
