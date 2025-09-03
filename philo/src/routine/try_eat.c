/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_eat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 13:47:39 by jweber            #+#    #+#             */
/*   Updated: 2025/09/03 11:39:32 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "routine.h"
#include "utils.h"
#include <pthread.h>
#include <unistd.h>

static int	prepare_eating_loop(t_philo *p_philo, int *p_stop,
				long long *p_last_meal);
static int	free_forks(t_philo *p_philo);

/* In this function the philosopher tries to eat 
*/
int	try_eat(t_philo *p_philo, long long *p_last_meal, int *p_stop)
{
	int			ret;

	ret = prepare_eating_loop(p_philo, p_stop, p_last_meal);
	if (ret != SUCCESS || *p_stop == TRUE)
		return (ret);
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

/*
 *	This function tries to setup the philosopher to eat !	
 *		-> check if other thread dies or if itself dies !
 *		-> It then try to take its right and left fork by calling
 *		the function try_take_forks() 
 *		-> is does this routine every 1000us
 *	if an error occurs or if a thread dies, it tells the thread to stop
 *	by returning a non zero value or by setting *p_stop to true respecitvely
*/
static int	prepare_eating_loop(t_philo *p_philo, int *p_stop,
				long long *p_last_meal)
{
	int	ret;
	int	can_eat;
	int	is_dead;
	int	right_fork_locked;
	int	left_fork_locked;

	can_eat = FALSE;
	right_fork_locked = FALSE;
	left_fork_locked = FALSE;
	while (can_eat != TRUE)
	{
		ret = check_death(p_philo, *p_last_meal, &is_dead);
		if (ret != SUCCESS || is_dead == TRUE)
		{
			*p_stop = TRUE;
			return (ret);
		}
		ret = try_take_forks(p_philo, &can_eat,
				&right_fork_locked, &left_fork_locked);
		if (ret != SUCCESS)
			return (ret);
		if (usleep(OPERATION_STEP) < 0)
			return (usleep_failure());
	}
	return (SUCCESS);
}

/* This function reputs the status of right and left forks to AVAILABLE
 * by locking the mutex associated with the forks !
 * if it fails to lock the mutexes it returns an error assoicated with 
 * the pthread_mutex_lock error
*/
static int	free_forks(t_philo *p_philo)
{
	int			ret;

	ret = pthread_mutex_lock(p_philo->p_right_fork_mutex);
	if (ret != 0)
	{
		return (ret);
	}
	*p_philo->p_right_fork = AVAILABLE;
	pthread_mutex_unlock(p_philo->p_right_fork_mutex);
	ret = pthread_mutex_lock(p_philo->p_left_fork_mutex);
	if (ret != 0)
	{
		return (ret);
	}
	*p_philo->p_left_fork = AVAILABLE;
	pthread_mutex_unlock(p_philo->p_left_fork_mutex);
	return (SUCCESS);
}
