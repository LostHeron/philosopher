/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_take_forks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 16:30:28 by jweber            #+#    #+#             */
/*   Updated: 2025/08/26 13:31:06 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

static int	try_lock_fork(pthread_mutex_t *p_fork_mutex, int *p_fork,
				int *p_fork_lock);
static int	free_fork(pthread_mutex_t *p_fork_mutex, int *p_fork);

int	try_take_forks(t_philo *p_philo, int *p_can_eat)
{
	int	ret;
	int	right_fork_locked;
	int	left_fork_locked;

	right_fork_locked = FALSE;
	left_fork_locked = FALSE;
	ret = try_lock_fork(p_philo->p_right_fork_mutex, p_philo->p_right_fork,
			&right_fork_locked);
	if (ret != 0)
	{
		// something else ?
		return (ret);
	}
	if (right_fork_locked == TRUE)
	{
		ret = try_lock_fork(p_philo->p_left_fork_mutex, p_philo->p_left_fork,
				&left_fork_locked);
		if (ret != 0)
		{
			// something else ?
			// free right fork ?? -> yes I think !
			return (ret);
		}
		if (left_fork_locked == TRUE)
		{
			*p_can_eat = TRUE;
		}
		else
		{
			ret = free_fork(p_philo->p_right_fork_mutex, p_philo->p_right_fork);
			if (ret != 0)
			{
				// what else to do ?
				return (ret);
			}
		}
	}
	return (SUCCESS);
}

static int	try_lock_fork(pthread_mutex_t *p_fork_mutex, int *p_fork,
				int *p_fork_lock)
{
	int	ret;

	ret = pthread_mutex_lock(p_fork_mutex);
	if (ret != 0)
		return (ret);
	if (*p_fork == AVAILABLE)
	{
		*p_fork = UNAVAILABLE;
		*p_fork_lock = TRUE;
	}
	pthread_mutex_unlock(p_fork_mutex);
	return (SUCCESS);
}

static int	free_fork(pthread_mutex_t *p_fork_mutex, int *p_fork)
{
	int	ret;

	ret = pthread_mutex_lock(p_fork_mutex);
	if (ret != 0)
	{
		// what to do in this case ?
		return (ret);
	}
	*p_fork = AVAILABLE;
	pthread_mutex_unlock(p_fork_mutex);
	return (SUCCESS);
}
