/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:42:08 by jweber            #+#    #+#             */
/*   Updated: 2025/08/20 16:51:57 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdlib.h>

int	init_forks(int nb_philo, t_forks *p_forks)
{
	int	i;

	p_forks->forks = malloc(nb_philo * sizeof(int));
	if (p_forks->forks == NULL)
		return (ERROR_MALLOC);
	p_forks->forks_mutex = malloc(nb_philo * sizeof(pthread_mutex_t));
	if (p_forks->forks_mutex == NULL)
		return (ERROR_MALLOC);
	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_init(p_forks->forks_mutex + i, NULL);
	}
	return (SUCCESS);
}
