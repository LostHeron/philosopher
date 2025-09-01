/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_sleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:19:48 by jweber            #+#    #+#             */
/*   Updated: 2025/08/27 18:39:36 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "routine.h"
#include "utils.h"
#include <unistd.h>

static int	check_finished_sleeping(long long sleep_start_time,
				int *p_done_sleeping, int time_to_sleep);

int	try_sleep(t_philo *p_philo, long long last_meal, int *p_stop)
{
	long long	sleep_start_time;
	int			is_dead;
	int			ret;
	int			done_sleeping;

	ret = ft_get_time(&sleep_start_time);
	if (ret != 0)
	{
		// do something else ?
		*p_stop = TRUE;
		return (ret);
	}
	ret = print_message_philo(p_philo->p_printf_mutex,
			sleep_start_time - p_philo->ref_time,
			p_philo->philo_id, "is sleeping");
	if (ret != 0)
	{
		// do something else ?
		*p_stop = TRUE;
		return (ret);
	}
	done_sleeping = FALSE;
	while (done_sleeping == FALSE)
	{
		usleep(OPERATION_STEP);
		ret = check_death(p_philo, last_meal, &is_dead);
		if (ret != 0)
		{
			// what to do return ?
			return (ret);
		}
		if (is_dead == TRUE)
		{
			*p_stop = TRUE;
			// something else ?
			return (ret);
		}
		ret = check_finished_sleeping(sleep_start_time, &done_sleeping,
				p_philo->time_to_sleep);
		if (ret != 0)
		{
			// kill the philo before exiting ?
			// in case of error ?
			return (ret);
		}
	}
	return (SUCCESS);
}

/* this function should
 * retrieve current_time, and check if 
 * current_time - sleep_start_time >= time_to_sleep
 * if (current_time - sleep_start_time >= time_to_sleep)
 *	set *p_finished_sleep to true;

*/
static int	check_finished_sleeping(long long sleep_start_time,
				int *p_done_sleeping, int time_to_sleep)
{
	long long	current_time;
	int			ret;

	ret = ft_get_time(&current_time);
	if (ret != 0)
	{
		// something else ?
		return (ret);
	}
	if (current_time - sleep_start_time >= time_to_sleep)
	{
		*p_done_sleeping = TRUE;
	}
	return (SUCCESS);
}
