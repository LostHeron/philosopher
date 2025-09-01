/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 10:46:07 by jweber            #+#    #+#             */
/*   Updated: 2025/08/27 14:11:43 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "philo.h"
#include "routine.h"
#include "utils.h"

/* This function should
 *	set *p_stop_exec to true, by locking mutex associated with the value before
 *	doing so
 *		-> If mutex_lock fail, return an error,
 *		-> else return (SUCCESS);
*/
int	try_kill_philo(pthread_mutex_t *p_stop_exec_mutex, int *p_stop_exec,
		t_philo *p_philo)
{
	int	ret;
	int	has_been_killed;
	long long current_time;

	ret = pthread_mutex_lock(p_stop_exec_mutex);
	if (ret != 0)
		return (ret);
	if (*p_stop_exec == FALSE)
	{
		*p_stop_exec = TRUE;
		has_been_killed = TRUE;
	}
	else
		has_been_killed = FALSE;
	pthread_mutex_unlock(p_stop_exec_mutex);
	if (has_been_killed == TRUE)
	{
		ret = ft_get_time(&current_time);
		if (ret != 0)
		{
			// do stuff
			return (ret);
		}
		print_message_philo(p_philo->p_printf_mutex,
			current_time - p_philo->ref_time,
			p_philo->philo_id, "died");
	}
	return (SUCCESS);
}
