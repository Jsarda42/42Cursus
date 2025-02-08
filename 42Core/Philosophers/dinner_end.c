/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_end.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:09:01 by juliensarda       #+#    #+#             */
/*   Updated: 2024/04/01 22:49:51 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destory_all(t_philo *philo, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	safe_mutex(&philo->prog->printf_lock, DESTROY);
	safe_mutex(&philo->prog->meal_lock, DESTROY);
	safe_mutex(&philo->prog->dead_lock, DESTROY);
	while (i < philo->num_of_philos)
	{
		safe_mutex(&forks[i], DESTROY);
		i++;
	}
}
