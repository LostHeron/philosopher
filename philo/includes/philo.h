/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:51:17 by jweber            #+#    #+#             */
/*   Updated: 2025/09/02 17:38:07 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

/* time to between each time we check if a philo died */
enum e_step
{
	OPERATION_STEP = 1000,
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

typedef struct s_simu_stat
{
	int	nb_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_time_each_one_eats;
}	t_simu_stat;

typedef struct s_mutexes
{
	int				*array_forks;
	pthread_mutex_t	*array_forks_mutex;
	int				stop_exec;
	pthread_mutex_t	stop_exec_mutex;
	pthread_mutex_t	nb_finished_eaten_mutex;
	int				nb_finished_eaten;
	pthread_mutex_t	start_mutex;
}				t_mutexes;

# define SIZE_BUF_PRINT 256

typedef struct s_philo
{
	char			buf_msg[SIZE_BUF_PRINT];
	size_t			buf_msg_len;
	int				philo_id;
	int				nb_time_to_eat;
	long long		ref_time;
	int				*p_left_fork;
	pthread_mutex_t	*p_left_fork_mutex;
	int				*p_right_fork;
	pthread_mutex_t	*p_right_fork_mutex;
	int				*p_stop_exec;
	pthread_mutex_t	*p_stop_exec_mutex;
	pthread_mutex_t	*p_nb_finished_eaten_mutex;
	int				*p_nb_finished_eaten;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	pthread_mutex_t	*p_start_mutex;
}				t_philo;

#endif
