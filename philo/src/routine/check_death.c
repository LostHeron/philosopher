/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:19:52 by jweber            #+#    #+#             */
/*   Updated: 2025/08/27 18:29:17 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "routine.h"
#include "utils.h"

static int	check_other_death(t_philo *p_philo, int *p_other_has_died);
static int	check_own_death(t_philo *p_philo, long long last_meal,
				int *p_has_died);

/* This function should check:
 *	-> First : if any other thread has died !
 *	-> Second : if this own thread just died !
 *	This function passes *p_is_dead to check_other_death and 
 *	check_own_death, it set *p_is_dead to TRUE if one other thread or
 *	this thread has died !
*/
int	check_death(t_philo *p_philo, long long last_meal, int *p_is_dead)
{
	int	ret;

	ret = check_other_death(p_philo, p_is_dead);
	if (ret != 0)
	{
		// some else ?
		return (ret);
	}
	ret = check_own_death(p_philo, last_meal, p_is_dead);
	if (ret != 0)
	{
		// some else ?
		return (ret);
	}
	return (SUCCESS);

}

/* This function should check if a philosopher has died
 *	-> if a philosopher has died, put *p_other_has_died to True,
 *	-> else put *p_other_has_died to_false;
*/
static int	check_other_death(t_philo *p_philo, int *p_other_has_died)
{
	int	ret;

	ret = pthread_mutex_lock(p_philo->p_stop_exec_mutex);
	if (ret != 0)
		return (ret);
	if (*p_philo->p_stop_exec == TRUE)
	{
		*p_other_has_died = TRUE;
	}
	else
	{
		*p_other_has_died = FALSE;
	}
	pthread_mutex_unlock(p_philo->p_stop_exec_mutex);
	return (SUCCESS);
}

/* This function should
 *	-> verify if the philosopher has not eating since more than 
 *	p_philo->time_to_die (comparing it against current_time - last_meal)
 *	if p_philo->time_to_die < (comparing it against current_time - last_meal)
 *	-> kill the philosopher and set *p_has_died to true;
 *	else set *p_has_died to false
*/
static int	check_own_death(t_philo *p_philo, long long last_meal,
				int *p_has_died)
{
	int			ret;
	long long	current_time;

	ret = ft_get_time(&current_time);
	if (ret != 0)
	{
		// what to do ? not free forks, should be done in same function that
		// took it in my mind.
		return (ret);
	}
	if (current_time - last_meal > p_philo->time_to_die)
	{
		*p_has_died = TRUE;
		ret = kill_philo(p_philo->p_stop_exec_mutex, p_philo->p_stop_exec);
		if (ret != 0)
		{
			// what to do ? it means it could not lock mutex
			// and say to other philo they should stop
			// hm, idk what to do !
			// just force the value being 1 without locking the mutex ?
			// think lated i guess !
			return (ret);
		}
	}
	else
	{
		*p_has_died = FALSE;
	}
	return (SUCCESS);
}
