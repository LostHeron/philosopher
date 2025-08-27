/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:42:08 by jweber            #+#    #+#             */
/*   Updated: 2025/08/21 14:38:55 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "ft_clear.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

static int	init_array_fork_mutex(int nb_philo, t_forks *p_forks);

/*		This function should initialize the different forks 
 *	and init each mutex associated with the forks 
*/
int	init_forks(int nb_philo, t_forks *p_forks)
{
	int	ret;
	int	i;

	p_forks->array_forks = malloc(nb_philo * sizeof(int));
	if (p_forks->array_forks == NULL)
		return (ERROR_MALLOC);
	i = 0;
	while (i < nb_philo)
	{
		p_forks->array_forks[i] = AVAILABLE;
		i++;
	}
	p_forks->array_forks_mutex = malloc(nb_philo * sizeof(pthread_mutex_t));
	if (p_forks->array_forks_mutex == NULL)
		return (ERROR_MALLOC);
	ret = init_array_fork_mutex(nb_philo, p_forks);
	if (ret != SUCCESS)
		return (ret);
	p_forks->stop_exec = FALSE;
	ret = pthread_mutex_init(&p_forks->stop_exec_mutex, NULL);
	if (ret < 0)
	{
		clear_mutex(p_forks, nb_philo);
		printf("failed to initialize mutexes\n");
		return (FAILURE);
	}
	ret = pthread_mutex_init(&p_forks->printf_mutex, NULL);
	if (ret < 0)
	{
		pthread_mutex_destroy(&p_forks->printf_mutex);
		clear_mutex(p_forks, nb_philo);
		printf("failed to initialize mutexes\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	init_array_fork_mutex(int nb_philo, t_forks *p_forks)
{
	int	i;
	int	ret;

	i = 0;
	while (i < nb_philo)
	{
		ret = pthread_mutex_init(p_forks->array_forks_mutex + i, NULL);
		if (ret != 0)
		{
			clear_mutex(p_forks, i);
			printf("failed to initialize mutexes\n");
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}
