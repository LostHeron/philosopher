/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arr_philo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 11:12:13 by jweber            #+#    #+#             */
/*   Updated: 2025/09/01 13:07:28 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

static void	fill_philo_i(t_philo **p_arr_philo, t_simu_stat simu_stat,
				t_mutexes mutexes, int i);

/*		This function should malloc an array of t_philo,
 *	and fill each philo to contain the correct left fork 
 *	right fork and mutex and stats from philo_stat
*/
int	init_arr_philo(t_simu_stat simu_stat,
			t_mutexes mutexes, t_philo **p_arr_philo)
{
	int	i;

	*p_arr_philo = malloc(simu_stat.nb_philo * sizeof(t_philo));
	if (*p_arr_philo == NULL)
		return (FAILURE);
	i = 0;
	while (i < simu_stat.nb_philo)
	{
		fill_philo_i(p_arr_philo, simu_stat, mutexes, i);
		i++;
	}
	return (0);
}

static void	fill_philo_i(t_philo **p_arr_philo, t_simu_stat simu_stat,
				t_mutexes mutexes, int i)
{
	(*p_arr_philo)[i].philo_id = i + 1;
	(*p_arr_philo)[i].p_left_fork = &mutexes.array_forks[i];
	(*p_arr_philo)[i].p_left_fork_mutex = &mutexes.array_forks_mutex[i];
	(*p_arr_philo)[i].p_right_fork
		= &mutexes.array_forks[(i + 1) % simu_stat.nb_philo];
	(*p_arr_philo)[i].p_right_fork_mutex
		= &mutexes.array_forks_mutex[(i + 1) % simu_stat.nb_philo];
	(*p_arr_philo)[i].p_stop_exec = &mutexes.stop_exec;
	(*p_arr_philo)[i].p_stop_exec_mutex = &mutexes.stop_exec_mutex;
	(*p_arr_philo)[i].time_to_die = simu_stat.time_to_die;
	(*p_arr_philo)[i].time_to_eat = simu_stat.time_to_eat;
	(*p_arr_philo)[i].time_to_sleep = simu_stat.time_to_sleep;
	(*p_arr_philo)[i].nb_time_to_eat = simu_stat.nb_time_each_one_eats;
	(*p_arr_philo)[i].p_printf_mutex = &mutexes.printf_mutex;
	(*p_arr_philo)[i].p_start_mutex = &mutexes.start_mutex;
}
