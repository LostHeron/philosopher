/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 13:37:04 by jweber            #+#    #+#             */
/*   Updated: 2025/08/21 15:59:46 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "routine.h"
#include <stdio.h>
#include <pthread.h>

void	*routine(void *args)
{
	t_philo			*p_philo;
	int				nb_time_eaten;
	int				stop_exec;

	p_philo = args;
	nb_time_eaten = 0;
	pthread_mutex_lock(p_philo->p_printf_mutex);
	printf("philo nb = %i\n", p_philo->philo_id);
	pthread_mutex_unlock(p_philo->p_printf_mutex);
	stop_exec = FALSE;
	while (stop_exec == FALSE && (p_philo->nb_time_to_eat < 0
			|| nb_time_eaten < p_philo->nb_time_to_eat))
	{
		try_eat(p_philo);
		nb_time_eaten++;
		try_think(p_philo);
		check_death(p_philo);
		try_sleep(p_philo);
		is_ok_check_other_ok();
	}
	return (NULL);
}
