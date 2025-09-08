/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_take_forks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 16:30:28 by jweber            #+#    #+#             */
/*   Updated: 2025/09/02 20:10:59 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "routine.h"
#include "utils.h"
#include <pthread.h>

static int	try_lock_fork_print(pthread_mutex_t *p_fork_mutex, int *p_fork,
				int *p_fork_locked, t_philo *p_philo);
static int	try_lock_fork(pthread_mutex_t *p_fork_mutex, int *p_fork,
				int *p_fork_lock);

/* to check
 *	-> first try_lock_fork_print fail : DONE -> OK !
 *	-> second try_lock_fork_print fail : DONE -> OK !
*/
int	try_take_forks(t_philo *p_philo, int *p_can_eat,
		int *p_right_fork_locked, int *p_left_fork_locked)
{
	int			ret;

	if (*p_right_fork_locked == FALSE)
	{
		ret = try_lock_fork_print(p_philo->p_right_fork_mutex,
				p_philo->p_right_fork, p_right_fork_locked, p_philo);
		if (ret != SUCCESS)
			return (ret);
	}
	if (*p_left_fork_locked == FALSE)
	{
		ret = try_lock_fork_print(p_philo->p_left_fork_mutex,
				p_philo->p_left_fork, p_left_fork_locked, p_philo);
		if (ret != SUCCESS)
			return (ret);
	}
	if (*p_left_fork_locked == TRUE && *p_right_fork_locked == TRUE)
	{
		*p_can_eat = TRUE;
	}
	return (SUCCESS);
}

/*	to check
 *		-> try_lock_fork fail : DONE -> OK !
 *		-> ft_get_time fail : DONE -> OK !
 *		-> print_message_philo fail : DONE -> OK !
*/
static int	try_lock_fork_print(pthread_mutex_t *p_fork_mutex, int *p_fork,
				int *p_fork_locked, t_philo *p_philo)
{
	int			ret;
	long long	current_time;

	ret = try_lock_fork(p_fork_mutex, p_fork,
			p_fork_locked);
	if (ret != SUCCESS)
		return (ret);
	if (*p_fork_locked == TRUE)
	{
		ret = ft_get_time(&current_time);
		if (ret != 0)
			return (ret);
		if (print_message_philo(p_philo,
				current_time - p_philo->ref_time,
				"has taken a fork") != SUCCESS)
			return (FAILURE);
	}
	return (SUCCESS);
}

/* to check
 *	-> pthread_mutex_lock fail : DONE -> OK !
*/
static int	try_lock_fork(pthread_mutex_t *p_fork_mutex, int *p_fork,
				int *p_fork_locked)
{
	int	ret;

	ret = pthread_mutex_lock(p_fork_mutex);
	if (ret != 0)
		return (pthread_mutex_lock_failure(ret));
	if (*p_fork == AVAILABLE)
	{
		*p_fork = UNAVAILABLE;
		*p_fork_locked = TRUE;
	}
	pthread_mutex_unlock(p_fork_mutex);
	return (SUCCESS);
}
