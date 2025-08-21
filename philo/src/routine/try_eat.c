/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_eat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 13:47:39 by jweber            #+#    #+#             */
/*   Updated: 2025/08/21 15:59:18 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "routine.h"
#include <pthread.h>
#include <unistd.h>

int	try_eat(t_philo *p_philo)
{
	int			ret;

	ret = print_message_philo(p_philo, "is eating");
	if (ret != 0)
		return (ret);
	//p_philo->nb_time_to_eat;
	pthread_mutex_lock(p_philo->p_right_fork_mutex);
	*p_philo->p_right_fork = UNAVAILABLE;
	pthread_mutex_lock(p_philo->p_left_fork_mutex);
	*p_philo->p_left_fork = UNAVAILABLE;
	// start eating
	usleep(OPERATION_STEP);
	check_death();
	*p_philo->p_right_fork = AVAILABLE;
	*p_philo->p_left_fork = AVAILABLE;
	pthread_mutex_unlock(p_philo->p_right_fork_mutex);
	pthread_mutex_unlock(p_philo->p_left_fork_mutex);
	// done eating 
	return (0);
}
