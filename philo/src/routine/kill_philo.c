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

/* This function should
 *	set *p_stop_exec to true, by locking mutex associated with the value before
 *	doing so
 *		-> If mutex_lock fail, return an error,
 *		-> else return (SUCCESS);
*/
int	kill_philo(pthread_mutex_t *p_stop_exec_mutex, int *p_stop_exec)
{
	int	ret;

	ret = pthread_mutex_lock(p_stop_exec_mutex);
	if (ret != 0)
		return (ret);
	*p_stop_exec = TRUE;
	pthread_mutex_unlock(p_stop_exec_mutex);
	return (SUCCESS);
}
