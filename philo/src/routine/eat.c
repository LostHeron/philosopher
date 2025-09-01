/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:07:50 by jweber            #+#    #+#             */
/*   Updated: 2025/08/27 18:38:50 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"
#include "routine.h"
#include <threads.h>
#include <unistd.h>

static int	check_finished_eating(long long eat_start_time, int *p_done_eating,
				int time_to_eat);

/* When entering this function, the philosopher start eating.
 * it should store the start time at which the philosopher start eating
 * this time will be used to compare if philo as finished eating !
 *	-> Then print a message anouncing the philosopher is eating !
 *	-> Then is should eat usleep after usleep, and check after each usleep:
 *		-> if any other thread has died
 *		-> if this thread just died
 *			if one of the two previous statement is true, stop execution
 *			by setting *p_stop to TRUE;
*/
int	eat(t_philo *p_philo, long long *p_last_meal, int *p_stop)
{
	long long	eat_start_time;
	int			done_eating;
	int			is_dead;
	int			ret;

	ret = ft_get_time(&eat_start_time);
	if (ret != 0)
	{
		// also say other thread this thread has died
		// free forks ?
		return (ret);
	}
	*p_last_meal = eat_start_time;
	ret = print_message_philo(p_philo->p_printf_mutex,
			eat_start_time - p_philo->ref_time,
			p_philo->philo_id, "is eating");
	if (ret != 0)
	{
		// also say other thread this thread has died
		// free forks ?
		return (ret);
	}
	done_eating = FALSE;
	while (done_eating == FALSE)
	{
		usleep(OPERATION_STEP);
		ret = check_death(p_philo, *p_last_meal, &is_dead);
		if (ret != 0 || is_dead == TRUE)
		{
			// what to do return ?
			*p_stop = TRUE;
			// something else ?
			return (ret);
		}
		ret = check_finished_eating(eat_start_time, &done_eating,
				p_philo->time_to_eat);
		if (ret != 0)
		{
			// kill the philo before exiting ?
			// in case of error ?
			return (ret);
		}
	}
	return (SUCCESS);
}

/* This should check if current philo as finished eating
 * by comparing current_time (retrieve in the function) - eat_start_time
 * with the time it takes to eat ! 
 * if thread as finished eating :
 *		set *p_done_eating to TRUE,
 *		set *p_last_meal to current_time,
 * else do nothing !
 * failure (case of function failure) : return non zero
 * sucess : return (0)
*/
static int	check_finished_eating(long long eat_start_time, int *p_done_eating,
				int time_to_eat)
{
	long long	current_time;
	int			ret;

	ret = ft_get_time(&current_time);
	if (ret != 0)
	{
		// do something else ? i'd say no do it in upper function !
		return (ret);
	}
	if (current_time - eat_start_time >= time_to_eat)
	{
		*p_done_eating = TRUE;
	}
	return (0);
}
