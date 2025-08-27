/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:49:08 by jweber            #+#    #+#             */
/*   Updated: 2025/08/27 16:35:43 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "routine.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

int	launch_philo(t_philo_stat *p_philo_stat, t_philo *arr_philo)
{
	int			i;
	pthread_t	*arr_th_philo;
	int			ret;

	arr_th_philo = malloc(p_philo_stat->nb_philo * sizeof(pthread_t));
	if (arr_th_philo == NULL)
		return (FAILURE);
	i = 0;
	while (i < p_philo_stat->nb_philo)
	{
		ret = pthread_create(arr_th_philo + i, NULL, &routine, arr_philo + i);
		if (ret != 0)
		{
			pthread_mutex_lock(arr_philo->p_printf_mutex);
			printf("pthread_create failed\n");
			pthread_mutex_unlock(arr_philo->p_printf_mutex);
		}
		else
		{
			pthread_mutex_lock(arr_philo->p_printf_mutex);
			printf("philo %i as been launched\n", i + 1);
			pthread_mutex_unlock(arr_philo->p_printf_mutex);
		}
		i++;
	}
	i = 0;
	while (i < p_philo_stat->nb_philo)
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
	return (0);
}
