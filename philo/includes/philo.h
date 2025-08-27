/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:51:17 by jweber            #+#    #+#             */
/*   Updated: 2025/08/27 18:42:58 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

/* time to between each time we check if a philo died */
enum e_step
{
	OPERATION_STEP = 5,
};

enum e_errors
{
	ERROR_MALLOC = -3,
	ERROR_WRITE = -4,
};

enum e_status
{
	SUCCESS,
	FAILURE,
};

enum e_bool
{
	FALSE,
	TRUE,
};

enum e_available
{
	AVAILABLE,
	UNAVAILABLE,
};

typedef struct s_philo_stat
{
	int	nb_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_time_each_one_eats;
}	t_philo_stat;

typedef struct s_forks
{
	int				*array_forks;
	pthread_mutex_t	*array_forks_mutex;
	int				stop_exec;
	pthread_mutex_t	stop_exec_mutex;
	pthread_mutex_t	printf_mutex;
}				t_forks;

typedef struct s_philo
{
	int				philo_id;
	int				nb_time_to_eat;
	long long		ref_time;
	int				*p_left_fork;
	pthread_mutex_t	*p_left_fork_mutex;
	int				*p_right_fork;
	pthread_mutex_t	*p_right_fork_mutex;
	int				*p_stop_exec;
	pthread_mutex_t	*p_stop_exec_mutex;
	pthread_mutex_t	*p_printf_mutex;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
}				t_philo;

#endif
