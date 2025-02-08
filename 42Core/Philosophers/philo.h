/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:19:59 by jsarda            #+#    #+#             */
/*   Updated: 2024/04/01 22:50:47 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# ifndef PHILO_MAX
#  define PHILO_MAX 200
# endif

typedef enum e_operation
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}					t_operation;

# define RST "\033[0m"
# define RED "\033[1;31m"
# define G "\033[1;32m"
# define Y "\033[1;33m"
# define B "\033[1;34m"
# define M "\033[1;35m"
# define C "\033[1;36m"
# define W "\033[1;37m"

typedef enum e_bool
{
	false,
	true
}					t_bool;

typedef struct s_prog
{
	int				dead_flag;
	pthread_mutex_t	printf_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
}					t_prog;

typedef struct s_philo
{
	int				id;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			num_of_philos;
	long			num_eat;
	pthread_mutex_t	*neighbor_fork;
	pthread_mutex_t	*philo_fork;
	size_t			start_time;
	size_t			last_meal;
	pthread_t		thread;
	t_prog			*prog;
	long			meal_eaten;
}					t_philo;

// error
void				error_exit(const char *error);

// utils
int					ft_strlen(char *str);
size_t				get_time_of_day(void);
void				print_message(int id, char *message, t_philo *philo);
void				usleep_breakdown(size_t time_ms);
void				thinking_time(t_philo *philo);
void				wait_before_start(t_philo *philo);

// init
void				parsing_init(t_philo *table, int argc, char **argv);
void				init_all(t_prog *prog, t_philo *philos,
						pthread_mutex_t *forks);

// threads
void				ft_threads(t_philo *philo);

// safe
void				safe_thread(pthread_t *thread, void *(*foo)(void *),
						t_philo *philo, t_operation operation);
void				safe_mutex(pthread_mutex_t *mutex, t_operation operation);

// routine
void				eating_routine(t_philo *philo);
void				*philo_routine(void *pointer);

// death
int					check_death(t_philo *philo);
void				destory_all(t_philo *philo, pthread_mutex_t *forks);

// check
int					all_eaten(t_philo *philo);
int					is_philo_dead(t_philo *philo);

#endif
