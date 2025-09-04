/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 12:28:59 by jweber            #+#    #+#             */
/*   Updated: 2025/09/04 15:22:16 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "ft_init.h"
#include "ft_clear.h"
#include <stdlib.h>

/* This function init both strucure : p_mutexe and p_arr_philo
 *		->p_mutexes : a pointer to a structure containing all mutexes needed
 *		->p_arr_philo : an array where each element correspond to the data needed
 *		by each philosopher for its execution
 *		p_arr_philo data arr filled from p_mutexes and philo_stat !
 *	to check :
 *		-> init_mutexes fail : DONE -> OK !
 *		-> init_arr_philo fial : DONE -> OK ! (have forgot to clear memory
 *		allocated in init_mutexes)
*/
int	init_philos(t_simu_stat simu_stat, t_mutexes *p_mutexes,
		t_philo **p_arr_philo)
{
	int	ret;

	ret = init_mutexes(simu_stat.nb_philos, p_mutexes);
	if (ret != SUCCESS)
	{
		return (FAILURE);
	}
	ret = init_arr_philo(simu_stat, p_mutexes, p_arr_philo);
	if (ret != SUCCESS)
	{
		clear_mutex(&p_mutexes->array_forks_mutex, simu_stat.nb_philos);
		free(p_mutexes->array_forks);
		p_mutexes->array_forks = NULL;
		pthread_mutex_destroy(&p_mutexes->stop_exec_mutex);
		pthread_mutex_destroy(&p_mutexes->nb_finished_eaten_mutex);
		pthread_mutex_destroy(&p_mutexes->start_mutex);
		return (FAILURE);
	}
	return (SUCCESS);
}
