/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:49:37 by jsarda            #+#    #+#             */
/*   Updated: 2024/04/01 19:11:32 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	mutex_error(int status, t_operation operation)
{
	if (0 == status)
		return ;
	if (EINVAL == status && (LOCK == operation || UNLOCK == operation))
		error_exit("The value specified by mutex is invalid");
	else if (EINVAL == status && INIT == operation)
		error_exit("The value specified by attr is invalid.");
	else if (EDEADLK == status)
		error_exit("A deadlock would occur if the thread "
			"blocked waiting for mutex.");
	else if (EPERM == status)
		error_exit("The current thread does not hold a lock on mutex.");
	else if (ENOMEM == status)
		error_exit("The process cannot allocate enough memory"
			" to create another mutex.");
	else if (EBUSY == status)
		error_exit("Mutex is locked");
}

static void	thread_error(int status, t_operation operation)
{
	if (status == 0)
		return ;
	if (EAGAIN == status)
		error_exit("No resources to create another thread");
	else if (EPERM == status)
		error_exit("The caller does not have appropriate permission\n");
	else if (EINVAL == status && CREATE == operation)
		error_exit("The value specified by attr is invalid.");
	else if (EINVAL == status && (JOIN == operation || DETACH == operation))
		error_exit("The value specified by thread is not joinable\n");
	else if (ESRCH == status)
		error_exit("No thread could be found corresponding to that"
			"specified by the given thread ID, thread.");
	else if (EDEADLK == status)
		error_exit("A deadlock was detected or the value of"
			"thread specifies the calling thread.");
}

void	safe_mutex(pthread_mutex_t *mutex, t_operation operation)
{
	if (LOCK == operation)
		mutex_error(pthread_mutex_lock(mutex), operation);
	else if (UNLOCK == operation)
		mutex_error(pthread_mutex_unlock(mutex), operation);
	else if (INIT == operation)
		mutex_error(pthread_mutex_init(mutex, NULL), operation);
	else if (DESTROY == operation)
		mutex_error(pthread_mutex_destroy(mutex), operation);
	else
		error_exit("Wrong operation for mutex_handle:"
			"use <LOCK> <UNLOCK> <INIT> <DESTROY>");
}

void	safe_thread(pthread_t *thread, void *(*foo)(void *), t_philo *philo,
		t_operation operation)
{
	if (CREATE == operation)
		thread_error(pthread_create(thread, NULL, foo, philo), operation);
	else if (JOIN == operation)
		thread_error(pthread_join(*thread, NULL), operation);
	else if (DETACH == operation)
		thread_error(pthread_detach(*thread), operation);
	else
		error_exit("You can only use:"
			"<CREATE> <JOIN> or <DETACH> threads operation !");
}
