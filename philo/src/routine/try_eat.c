/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_eat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 13:47:39 by jweber            #+#    #+#             */
/*   Updated: 2025/08/27 18:38:53 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "routine.h"
#include "utils.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static int	free_forks(t_philo *p_philo);

/* this function should make the philosopher eat
 * step by step, using OPERATION STEP;
 * after each step, it should: 
 *	-> check if any other philosopher as died, by locking
 *		the mutex associated with p_stop_exec, if one as died,
 *		then we must return and stop the execution;
 *	-> then check if the philosopher died, and if so, 
 *		it should update the value p_philo->p_stop_exec, 
 *		by first locking the mutex
 * This function should :
 *	-> return (1) if any thing had an error, or if we should stop the 
 *	execution 
 *	-> return (0) if everything happened well and execution should continue;
 *	args:
 *		-> last_meal : time this thread last ate (to compare if thread died !)
*/
int	try_eat(t_philo *p_philo, long long *p_last_meal, int *p_stop)
{
	int			ret;
	int			can_eat;
	int			is_dead;
	int			right_fork_locked;
	int			left_fork_locked;

	can_eat = FALSE;
	right_fork_locked = FALSE;
	left_fork_locked = FALSE;
	while (can_eat != TRUE)
	{
		ret = check_death(p_philo, *p_last_meal, &is_dead);
		if (ret != 0 || is_dead == TRUE)
		{
			*p_stop = TRUE;
			return (ret);
		}
		ret = try_take_forks(p_philo, &can_eat,
				&right_fork_locked, &left_fork_locked);
		if (ret != 0)
		{
			return (ret);
		}
		usleep(OPERATION_STEP);
	}
	ret = eat(p_philo, p_last_meal, p_stop);
	if (ret != 0 || *p_stop == TRUE)
	{
		free_forks(p_philo);
		return (ret);
	}
	ret = free_forks(p_philo);
	if (ret != 0)
	{
		return (ret);
	}
	return (SUCCESS);
}

/* This function reputs the status of right and left forks to AVAILABLE
 * by locking the mutex associated with the forks !
 *
*/
static int	free_forks(t_philo *p_philo)
{
	int	ret;

	ret = pthread_mutex_lock(p_philo->p_right_fork_mutex);
	if (ret != 0)
	{
		return (ret);
	}
	*p_philo->p_right_fork = AVAILABLE;
	pthread_mutex_unlock(p_philo->p_right_fork_mutex);
	long long current_time;
	ft_get_time(&current_time);
	print_message_philo(p_philo->p_printf_mutex,
		current_time - p_philo->ref_time,
		p_philo->philo_id, "has drop a fork");
	ret = pthread_mutex_lock(p_philo->p_left_fork_mutex);
	if (ret != 0)
	{
		return (ret);
	}
	*p_philo->p_left_fork = AVAILABLE;
	pthread_mutex_unlock(p_philo->p_left_fork_mutex);
	return (SUCCESS);
}
