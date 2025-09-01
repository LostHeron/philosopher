/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:49:08 by jweber            #+#    #+#             */
/*   Updated: 2025/09/01 13:11:54 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "routine.h"
#include "utils.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

static int	init_ref_time(t_philo *arr_philo, int nb_philo);

int	launch_philo(t_simu_stat *p_simu_stat, t_philo *arr_philo)
{
	int			i;
	pthread_t	*arr_th_philo;
	int			ret;

	arr_th_philo = malloc(p_simu_stat->nb_philo * sizeof(pthread_t));
	if (arr_th_philo == NULL)
		return (FAILURE);
	i = 0;
	pthread_mutex_lock(arr_philo->p_start_mutex);
	while (i < p_simu_stat->nb_philo)
	{
		ret = pthread_create(arr_th_philo + i, NULL, &routine, arr_philo + i);
		if (ret != 0)
		{
			pthread_mutex_lock(arr_philo->p_printf_mutex);
			printf("pthread_create failed\n");
			pthread_mutex_unlock(arr_philo->p_printf_mutex);
			// should also set p_stop_exec to TRUE,
			// so execution do not start in already started thread !
			break;
		}
		else
		{
			pthread_mutex_lock(arr_philo->p_printf_mutex);
			printf("philo %i as been launched\n", i + 1);
			pthread_mutex_unlock(arr_philo->p_printf_mutex);
		}
		i++;
	}
	init_ref_time(arr_philo, p_simu_stat->nb_philo);
	pthread_mutex_unlock(arr_philo->p_start_mutex);
	i = 0;
	while (i < p_simu_stat->nb_philo)
	{
		ret = pthread_join(arr_th_philo[i], NULL);
		if (ret != 0)
		{
			pthread_mutex_lock(arr_philo->p_printf_mutex);
			printf("pthread_join failed\n");
			pthread_mutex_unlock(arr_philo->p_printf_mutex);
		}
		else
		{
			pthread_mutex_lock(arr_philo->p_printf_mutex);
			printf("philo %i as been joined\n", i + 1);
			pthread_mutex_unlock(arr_philo->p_printf_mutex);
		}
		i++;
	}
	free(arr_th_philo);
	return (SUCCESS);
}

static int	init_ref_time(t_philo *arr_philo, int nb_philo)
{
	int			i;
	int			ret;
	long long	ref_time;

	ret = ft_get_time(&ref_time);
	if (ret != 0)
	{
		return (ret);
	}
	i = 0;
	while (i < nb_philo)
	{
		arr_philo[i].ref_time = ref_time;
		i++;
	}
	return (SUCCESS);
}
