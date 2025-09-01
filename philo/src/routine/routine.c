/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 13:37:04 by jweber            #+#    #+#             */
/*   Updated: 2025/09/01 15:17:05 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"
#include "routine.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/* This is the main starting point for each thread !
 * if a thread need to be killed, it should be done here ?
*/
void	*routine(void *args)
{
	t_philo		*p_philo;
	int			nb_time_eaten;
	int			stop;
	int			ret;
	long long	last_meal;

	p_philo = args;
	ret = pthread_mutex_lock(p_philo->p_start_mutex);
	if (ret != 0)
	{
		ft_putstr_fd("could not lock start mutex, aborting\n", 2);
		return (NULL);
	}
	pthread_mutex_unlock(p_philo->p_start_mutex);
	last_meal = p_philo->ref_time;
	ret = check_death(p_philo, last_meal, &stop);
	if (ret != 0)
	{
		// do stuff ?
		return (NULL);
	}
	if (stop == TRUE)
	{
		// do stuff ?
		return (NULL);
	}
	nb_time_eaten = 0;
	stop = FALSE;
	ret = try_think(p_philo, &stop);
	if (ret != 0 || stop == TRUE)
	{
		return (NULL);//
	}
	if (p_philo->philo_id % 2 == 0)
	{
		usleep(p_philo->time_to_eat * 1000 / 2);
	}
	while (stop == FALSE && (p_philo->nb_time_to_eat < 0
			|| nb_time_eaten < p_philo->nb_time_to_eat))
	{
		ret = try_eat(p_philo, &last_meal, &stop);
		if (ret != 0 || stop == TRUE)
		{
			/*
			int	new_ret;
			new_ret = try_kill_philo(p_philo->p_stop_exec_mutex,
					p_philo->p_stop_exec);
			if (new_ret != 0)
			{
				// what to do ?
			}
			*/
			ft_putstr_fd("we exit routineafter try eat!\n", 2);
			return (NULL);
		}
		nb_time_eaten++;
		ret = try_sleep(p_philo, last_meal, &stop);
		if (ret != 0 || stop == TRUE)
		{
			ft_putstr_fd("we exit routine after try sleep!\n", 2);
			return (NULL);//
		}
		ret = try_think(p_philo, &stop);
		if (ret != 0 || stop == TRUE)
		{
			ft_putstr_fd("we exit routine after try think!\n", 2);
			return (NULL);//
		}
	}
	long long	current_time;
	ft_get_time(&current_time);
	print_message_philo(p_philo->p_printf_mutex,
		current_time - p_philo->ref_time,
		p_philo->philo_id, "OUT OF LOOP\n");
	return (NULL);
}
