/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 08:40:54 by juliensarda       #+#    #+#             */
/*   Updated: 2024/03/27 14:18:05 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_philo_dead(t_philo *philo)
{
	safe_mutex(&philo->prog->dead_lock, LOCK);
	if (philo->prog->dead_flag == 1)
	{
		safe_mutex(&philo->prog->dead_lock, UNLOCK);
		return (1);
	}
	safe_mutex(&philo->prog->dead_lock, UNLOCK);
	return (0);
}
