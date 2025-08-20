/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:17:49 by jweber            #+#    #+#             */
/*   Updated: 2025/08/20 17:20:18 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdlib.h>

void	clear_mutex(t_forks *p_forks, int nb_clear)
{
	int	i;

	free(p_forks->forks);
	i = 0;
	while (i < nb_clear)
	{
		pthread_mutex_destroy(p_forks->forks_mutex + i);
	}
	free(p_forks->forks_mutex);
	return ;
}
