/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:51:17 by jweber            #+#    #+#             */
/*   Updated: 2025/08/20 16:50:09 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

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
	int				*forks;
	pthread_mutex_t	*forks_mutex;
}				t_forks;

enum e_errors
{
	ERROR_MALLOC = -3,
};

enum e_status
{
	SUCCESS,
	FAILURE,
};

#endif
