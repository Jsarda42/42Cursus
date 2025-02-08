/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 22:53:34 by jsarda            #+#    #+#             */
/*   Updated: 2024/04/01 22:54:12 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	usleep_breakdown(size_t time_ms)
{
	ssize_t	time_us;

	time_us = time_ms * 1000;
	usleep(time_us);
}

void	wait_before_start(t_philo *philo)
{
	if (philo->num_of_philos == 1)
	{
		return ;
	}
	if (philo->id % 2 == 1)
	{
		print_message(philo->id, "is thinking", philo);
	}
	if (philo->id == philo->num_of_philos && philo->num_of_philos % 2 == 1)
	{
		usleep(philo->time_to_eat * 2 * 1000);
	}
	else if (philo->id % 2 == 1)
		usleep(philo->time_to_eat * 1000);
}

void	thinking_time(t_philo *philo)
{
	if (philo->num_of_philos % 2 == 0)
	{
		if ((philo->time_to_eat - philo->time_to_sleep) > 0)
		{
			usleep(((philo->time_to_eat) - philo->time_to_sleep) * 1000);
		}
	}
	else
	{
		if (((philo->time_to_eat * 2) - philo->time_to_sleep) > 0)
		{
			usleep(((philo->time_to_eat * 2) - philo->time_to_sleep) * 1000);
		}
	}
}
