/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:20:27 by jweber            #+#    #+#             */
/*   Updated: 2025/09/04 15:55:26 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"
#include <pthread.h>

int	join_philos(pthread_t *arr_th_philo, int nb_to_join)
{
	int	final_ret;
	int	ret;
	int	i;

	i = 0;
	final_ret = SUCCESS;
	while (i < nb_to_join)
	{
		ret = pthread_join(arr_th_philo[i], NULL);
		if (ret != 0)
		{
			ft_putstr_fd("pthread_join failed\n", 2);
			final_ret = FAILURE;
		}
		i++;
	}
	return (final_ret);
}
