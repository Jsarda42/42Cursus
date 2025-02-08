/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:41:33 by jsarda            #+#    #+#             */
/*   Updated: 2024/04/01 22:14:07 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_dead_flag_lock(t_philo *philo)
{
	int	tmp_dead_flag;

	safe_mutex(&philo->prog->dead_lock, LOCK);
	tmp_dead_flag = philo->prog->dead_flag;
	safe_mutex(&philo->prog->dead_lock, UNLOCK);
	return (tmp_dead_flag);
}

void	manage_one_philo(t_philo *philo)
{
	usleep_breakdown(philo->time_to_die);
	print_message(philo->id, "died", philo);
	safe_mutex(philo->philo_fork, UNLOCK);
	safe_mutex(&philo->prog->dead_lock, LOCK);
	philo->prog->dead_flag = 1;
	safe_mutex(&philo->prog->dead_lock, UNLOCK);
}

void	eating_routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
		safe_mutex(philo->neighbor_fork, LOCK);
	else
		safe_mutex(philo->philo_fork, LOCK);
	print_message(philo->id, "has taken a fork", philo);
	if (philo->num_of_philos == 1)
	{
		manage_one_philo(philo);
		return ;
	}
	if (philo->id % 2 == 0)
		safe_mutex(philo->philo_fork, LOCK);
	else
		safe_mutex(philo->neighbor_fork, LOCK);
	print_message(philo->id, "has taken a fork", philo);
	safe_mutex(&philo->prog->meal_lock, LOCK);
	philo->last_meal = get_time_of_day();
	safe_mutex(&philo->prog->meal_lock, UNLOCK);
	print_message(philo->id, "is eating", philo);
	usleep_breakdown(philo->time_to_eat);
	safe_mutex(&philo->prog->meal_lock, LOCK);
	philo->meal_eaten = philo->meal_eaten + 1;
	safe_mutex(&philo->prog->meal_lock, UNLOCK);
	safe_mutex(philo->neighbor_fork, UNLOCK);
	safe_mutex(philo->philo_fork, UNLOCK);
}

void	sleeping_routine(t_philo *philo)
{
	print_message(philo->id, "is sleeping", philo);
	usleep_breakdown(philo->time_to_sleep);
}

void	*philo_routine(void *pointer)
{
	t_philo	*philo;
	int		tmp_dead_flag;

	philo = (t_philo *)pointer;
	if (!philo)
		return (NULL);
	tmp_dead_flag = mutex_dead_flag_lock(philo);
	wait_before_start(philo);
	while (tmp_dead_flag != 1)
	{
		tmp_dead_flag = mutex_dead_flag_lock(philo);
		eating_routine(philo);
		sleeping_routine(philo);
		print_message(philo->id, "is thinking", philo);
		thinking_time(philo);
	}
	return (NULL);
}
