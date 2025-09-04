/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:49:08 by jweber            #+#    #+#             */
/*   Updated: 2025/09/01 15:10:17 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "routine.h"
#include "utils.h"
#include <pthread.h>
#include <stdlib.h>

static int	pthread_create_failure(pthread_mutex_t *p_stop_exec_mutex,
				int *p_stop_exec, pthread_mutex_t *p_start_mutex);
static int	init_ref_time(t_philo *arr_philo, int nb_philo);

int	create_philos(pthread_t *arr_th_philo, t_simu_stat *p_simu_stat,
		t_philo *arr_philos, int *p_nb_th_launched)
{
	int			ret;

	*p_nb_th_launched = 0;
	pthread_mutex_lock(arr_philos->p_start_mutex);
	while (*p_nb_th_launched < p_simu_stat->nb_philo)
	{
		ret = pthread_create(arr_th_philo + (*p_nb_th_launched), NULL, &routine,
				arr_philos + (*p_nb_th_launched));
		if (ret != 0)
			return (pthread_create_failure(arr_philos->p_stop_exec_mutex,
					arr_philos->p_stop_exec, arr_philos->p_start_mutex));
		(*p_nb_th_launched)++;
	}
	ret = init_ref_time(arr_philos, p_simu_stat->nb_philo);
	if (ret != SUCCESS)
	{
		return (ret);
	}
	pthread_mutex_unlock(arr_philos->p_start_mutex);
	return (SUCCESS);
}

static int	pthread_create_failure(pthread_mutex_t *p_stop_exec_mutex,
				int *p_stop_exec, pthread_mutex_t *p_start_mutex)
{
	int	ret;

	ft_putstr_fd("pthread_create failed\n", 2);
	ret = pthread_mutex_lock(p_stop_exec_mutex);
	if (ret != 0)
	{
		ft_putstr_fd("could not lock stop_exec_mutex ->"
			" critical error in program behaviour\n", 2);
		pthread_mutex_unlock(p_start_mutex);
		*p_stop_exec = TRUE;
		return (ret);
	}
	*p_stop_exec = TRUE;
	pthread_mutex_unlock(p_stop_exec_mutex);
	pthread_mutex_unlock(p_start_mutex);
	return (ret);
}

static int	init_ref_time(t_philo *arr_philo, int nb_philo)
{
	int			i;
	int			ret;
	long long	ref_time;

	ret = ft_get_time(&ref_time);
	if (ret != 0)
		return (ret);
	i = 0;
	while (i < nb_philo)
	{
		arr_philo[i].ref_time = ref_time;
		i++;
	}
	return (SUCCESS);
}
