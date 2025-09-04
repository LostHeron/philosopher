/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 12:38:55 by jweber            #+#    #+#             */
/*   Updated: 2025/09/04 15:23:50 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "ft_clear.h"
#include <pthread.h>
#include <stdlib.h>

void	clear_all(t_mutexes *p_mutexes, t_philo **p_arr_philo, int nb_philo)
{
	clear_mutex(&p_mutexes->array_forks_mutex, nb_philo);
	free(p_mutexes->array_forks);
	p_mutexes->array_forks = NULL;
	free(*p_arr_philo);
	*p_arr_philo = NULL;
	pthread_mutex_destroy(&p_mutexes->stop_exec_mutex);
	pthread_mutex_destroy(&p_mutexes->nb_finished_eaten_mutex);
	pthread_mutex_destroy(&p_mutexes->start_mutex);
	return ;
}
