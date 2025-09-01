/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:37:04 by jweber            #+#    #+#             */
/*   Updated: 2025/08/27 18:36:47 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "ft_init.h"
#include "execution.h"
#include "ft_clear.h"
#include <pthread.h>
#include <stdlib.h>

int	start_philo(t_philo_stat philo_stat)
{
	t_forks			forks;
	t_philo			*arr_philo;
	int				ret;

	ret = init_forks(philo_stat.nb_philo, &forks);
	if (ret != SUCCESS)
	{
		return (FAILURE);
	}
	ret = init_arr_philo(philo_stat, forks, &arr_philo);
	if (ret != SUCCESS)
	{
		// do stuff ?
		return (FAILURE);
	}
	ret = launch_philo(&philo_stat, arr_philo);
	clear_mutex(&forks.array_forks_mutex, philo_stat.nb_philo);
	free(arr_philo);
	pthread_mutex_destroy(&forks.stop_exec_mutex);
	pthread_mutex_destroy(&forks.printf_mutex);
	pthread_mutex_destroy(&forks.start_mutex);
	return (ret);
}
