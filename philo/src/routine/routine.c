/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 13:37:04 by jweber            #+#    #+#             */
/*   Updated: 2025/09/04 19:58:29 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"
#include "routine.h"
#include <pthread.h>
#include <unistd.h>

static int	routine_init(t_philo *p_philo, long long *p_last_meal,
				int *p_stop, int *p_nb_time_eaten);
static int	routine_loop(t_philo *p_philo, long long *p_last_meal,
				int *p_stop, int *p_nb_time_eaten);
static void	set_stop_to_true(t_philo *p_philo);

/* This is the main starting point for each thread !
 * Two function call in this one :
 *		-> routine_init : see there for more detail
 *		-> routine_loop : see there for more detail
 * This is the function responsible for the handling its own thread
 *	-> IN CASE OF ERROR : if an error occurs in the function down under,
 *	(meaning return value of the function it calls is non zero)
 *	the execution of this thread should stop and it should put 
 *	p_philo->p_stop_exec to true by, first trying to lock the mutex
 *	associated with it, but if it fails, 
 *	forcing it causing a data ok, but yet assuring 
 *	but assuring that other thread will know it is locked !
 *
 *	to check : 
 *		-> routine_init fail : DONE -> OK !
 *		-> routine_loop fail : DONE -> OK !
*/
void	*routine(void *args)
{
	t_philo		*p_philo;
	int			nb_time_eaten;
	int			stop;
	int			ret;
	long long	last_meal;

	p_philo = args;
	ret = routine_init(p_philo, &last_meal, &stop, &nb_time_eaten);
	if (ret != SUCCESS)
	{
		set_stop_to_true(p_philo);
		return (NULL);
	}
	while (ret == SUCCESS && stop == FALSE)
	{
		ret = routine_loop(p_philo, &last_meal, &stop, &nb_time_eaten);
	}
	if (ret != SUCCESS)
	{
		set_stop_to_true(p_philo);
	}
	return (NULL);
}

/* This function initialize the routine :
 *	-> set last_meal to ref_time
 *	-> set nb_time_eaten to 0
 *	-> set stop to FALSE
 *	-> set check_death (if something happened wrong in creating all thread)
 *	-> then start thinking
 *	-> then make even philosopher wait for half eating time
 *		which let odd philosopher all eat at the same time
 *		execpt for one if the number of philosopher is odd 
 *
 *	To check : 
 *		-> first pthread_mutex_lock fail : DONE -> OK !
 *		-> check_death fail : DONE -> OK !
 *		-> try_think fail : DONE -> OK !
 *		-> wait_to_shift_even_philos fial: DONE -> OK !
*/
static int	routine_init(t_philo *p_philo, long long *p_last_meal,
				int *p_stop, int *p_nb_time_eaten)
{
	int	ret;

	ret = pthread_mutex_lock(p_philo->p_start_mutex);
	if (ret != 0)
		return (pthread_mutex_lock_failure(FAILURE));
	pthread_mutex_unlock(p_philo->p_start_mutex);
	*p_last_meal = p_philo->ref_time;
	*p_nb_time_eaten = 0;
	*p_stop = FALSE;
	ret = check_death(p_philo, *p_last_meal, p_stop);
	if (ret != 0 || *p_stop == TRUE)
		return (ret);
	ret = try_think(p_philo);
	if (ret != SUCCESS)
		return (ret);
	if (p_philo->philo_id % 2 == 0)
		if (wait_to_shift_even_philos(p_philo, p_stop,
				*p_last_meal, p_philo->time_to_eat / 2) != SUCCESS)
			return (FAILURE);
	return (SUCCESS);
}

/* This is the things that are executed in the while loop
 *	-> it will try to eat,
 *	-> once done, it will try to sleep
 *	-> once done, it will try to think
 *	-> so on until, either a philosopher dies or all philosopher 
 *	have eaten enough time !
 *
 *	to check : 
 *		-> try_eat fail : DONE -> OK !
 *		-> try_sleep fail : DONE -> OK !
 *		-> try_think fail : DONE -> OK !
*/
static int	routine_loop(t_philo *p_philo, long long *p_last_meal,
				int *p_stop, int *p_nb_time_eaten)
{
	int	ret;

	ret = try_eat(p_philo, p_last_meal, p_stop, p_nb_time_eaten);
	if (ret != 0 || *p_stop == TRUE)
	{
		return (ret);
	}
	ret = try_sleep(p_philo, *p_last_meal, p_stop);
	if (ret != 0 || *p_stop == TRUE)
	{
		return (ret);
	}
	ret = try_think(p_philo);
	if (ret != SUCCESS)
	{
		return (ret);
	}
	return (SUCCESS);
}

/* This function try to set p_stop_exec to true by first trying to
 * lock the mutex associated with it but then forcing it,
 * if it fails to lock the mutex to make sure other thread stop their execution
*/
static void	set_stop_to_true(t_philo *p_philo)
{
	int	ret;

	ret = pthread_mutex_lock(p_philo->p_stop_exec_mutex);
	if (ret != 0)
		pthread_mutex_lock_failure(ret);
	*p_philo->p_stop_exec = TRUE;
	pthread_mutex_unlock(p_philo->p_stop_exec_mutex);
	p_philo->return_value = FAILURE;
	return ;
}
