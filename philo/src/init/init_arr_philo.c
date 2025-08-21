/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arr_philo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 11:12:13 by jweber            #+#    #+#             */
/*   Updated: 2025/08/21 13:14:40 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

/*		This function should malloc an array of t_philo,
 *	and fill each philo to contain the correct left fork 
 *	right fork and mutex and stats from philo_stat
*/
int	init_arr_philo(t_philo_stat philo_stat,
			t_forks forks, t_philo **p_arr_philo)
{
	int	i;

	*p_arr_philo = malloc(philo_stat.nb_philo * sizeof(t_philo));
	if (*p_arr_philo == NULL)
		return (ERROR_MALLOC);
	i = 0;
	while (i < philo_stat.nb_philo)
	{
		(*p_arr_philo)[i].philo_id = i + 1;
		(*p_arr_philo)[i].p_left_fork = &forks.array_forks[i];
		(*p_arr_philo)[i].p_left_fork_mutex = &forks.array_forks_mutex[i];
		(*p_arr_philo)[i].p_right_fork
			= &forks.array_forks[(i + 1) % philo_stat.nb_philo];
		(*p_arr_philo)[i].p_right_fork_mutex
			= &forks.array_forks_mutex[(i + 1) % philo_stat.nb_philo];
		(*p_arr_philo)[i].p_stop_exec = &forks.stop_exec;
		(*p_arr_philo)[i].p_stop_exec_mutex = &forks.stop_exec_mutex;
		(*p_arr_philo)[i].time_to_die = philo_stat.time_to_die;
		(*p_arr_philo)[i].time_to_eat = philo_stat.time_to_eat;
		(*p_arr_philo)[i].time_to_sleep = philo_stat.time_to_sleep;
		(*p_arr_philo)[i].nb_time_to_eat = philo_stat.nb_time_each_one_eats;
		(*p_arr_philo)[i].p_printf_mutex = &forks.printf_mutex;
		i++;
	}
	return (0);
}
