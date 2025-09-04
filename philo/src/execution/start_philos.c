/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:37:04 by jweber            #+#    #+#             */
/*   Updated: 2025/09/01 15:10:41 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "execution.h"
#include "utils.h"
#include <pthread.h>
#include <stdlib.h>

int	start_philos(t_simu_stat simu_stat, t_philo **p_arr_philo)
{
	int			final_ret;
	int			ret;
	int			nb_th_launched;
	pthread_t	*arr_th_philo;

	arr_th_philo = malloc(simu_stat.nb_philo * sizeof(pthread_t));
	if (arr_th_philo == NULL)
		return (FAILURE);
	ret = create_philos(arr_th_philo, &simu_stat, *p_arr_philo,
			&nb_th_launched);
	if (ret != 0)
	{
		ft_putstr_fd("error while creating threads", 2);
		final_ret = ret;
	}
	ret = join_philos(arr_th_philo, nb_th_launched);
	if (ret != 0)
	{
		ft_putstr_fd("error while joining threads", 2);
		if (final_ret == 0)
			final_ret = ret;
	}
	free(arr_th_philo);
	return (ret);
}
