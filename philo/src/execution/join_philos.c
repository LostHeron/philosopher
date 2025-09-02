/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:20:27 by jweber            #+#    #+#             */
/*   Updated: 2025/09/01 15:06:26 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"
#include <pthread.h>
#include <stdio.h>

int	join_philos(pthread_t *arr_th_philo, pthread_mutex_t *p_printf_mutex,
		int nb_to_join)
{
	int	ret;
	int	i;

	i = 0;
	while (i < nb_to_join)
	{
		ret = pthread_join(arr_th_philo[i], NULL);
		if (ret != 0)
		{
			pthread_mutex_lock(p_printf_mutex);
			ft_putstr_fd("pthread_join failed\n", 2);
			pthread_mutex_unlock(p_printf_mutex);
		}
		else
		{
			pthread_mutex_lock(p_printf_mutex);
			//printf("philo %i as been joined\n", i + 1);
			pthread_mutex_unlock(p_printf_mutex);
		}
		i++;
	}
	return (SUCCESS);
}
