/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:07:50 by jweber            #+#    #+#             */
/*   Updated: 2025/09/04 17:34:11 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"
#include "routine.h"
#include <threads.h>
#include <unistd.h>

static int	eating_loop(t_philo *p_philo, long long eat_start_time,
				int *p_stop, long long last_meal);
static int	check_finished_eating(long long eat_start_time, int *p_done_eating,
				int time_to_eat);

/* When entering this function, the philosopher start eating.
 * it should store the start time at which the philosopher start eating
 * this time will be used to compare if philo as finished eating !
 *	-> Then print a message anouncing the philosopher is eating !
 *	-> Then is should check usleep after usleep:
 *		-> if any philosopher died !
 *		-> then if it finished eaten !
 *	if an error occured or a philosopher died, it should tell calling
 *	function to stop thread execution by returning a non null integer 
 *	or by setting *p_stop to TRUE respectively
 *
 *	to check :
 *		-> ft_get_time fail : DONE -> OK !
 *		-> print_message_philo_eating fail : DONE -> OK !
 *		-> eating_loop fail : DONE -> OK !
*/
int	eat(t_philo *p_philo, long long *p_last_meal, int *p_stop,
		int *p_nb_time_eaten)
{
	long long	eat_start_time;
	int			ret;

	ret = ft_get_time(&eat_start_time);
	if (ret != SUCCESS)
		return (ret);
	*p_last_meal = eat_start_time;
	(*p_nb_time_eaten)++;
	ret = print_message_philo_eating(p_philo, p_nb_time_eaten,
			eat_start_time - p_philo->ref_time,
			"is eating");
	if (ret != SUCCESS)
		return (ret);
	ret = eating_loop(p_philo, eat_start_time, p_stop, *p_last_meal);
	return (ret);
}

/* This function will wait usleep after usleep that the philosopher 
 * have finished eating
 * after each usleep, it : 
 *	-> check if any philosopher died
 *	-> then check if the philosopher finised eating !
 *
 *	to check
 *		-> usleep fail : DONE -> OK !
 *		-> check_death fail : DONE -> OK !
 *		-> check_finished_eating fail : DONE -> OK !
*/
static int	eating_loop(t_philo *p_philo, long long eat_start_time,
				int *p_stop, long long last_meal)
{
	int	ret;
	int	done_eating;
	int	is_dead;

	ret = SUCCESS;
	done_eating = FALSE;
	while (ret == SUCCESS && done_eating == FALSE)
	{
		if (usleep(OPERATION_STEP) < 0)
			return (usleep_failure());
		ret = check_death(p_philo, last_meal, &is_dead);
		if (ret != 0 || is_dead == TRUE)
		{
			*p_stop = TRUE;
			return (ret);
		}
		ret = check_finished_eating(eat_start_time, &done_eating,
				p_philo->time_to_eat);
	}
	return (ret);
}

/*	to check :
 *		-> ft_get_time fail : DONE -> OK !
*/
static int	check_finished_eating(long long eat_start_time, int *p_done_eating,
				int time_to_eat)
{
	long long	current_time;
	int			ret;

	ret = ft_get_time(&current_time);
	if (ret != SUCCESS)
	{
		return (ret);
	}
	if (current_time - eat_start_time >= time_to_eat)
	{
		*p_done_eating = TRUE;
	}
	return (SUCCESS);
}
