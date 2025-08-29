/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:17:49 by jweber            #+#    #+#             */
/*   Updated: 2025/08/21 11:27:47 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>

/* This function take an array of nb_to_clear mutexes,
 * it destroys each mutexes one by one then free the array of mutexes !
*/
void	clear_mutex(pthread_mutex_t *array_forks_mutex, int nb_to_clear)
{
	int	i;

	i = 0;
	while (i < nb_to_clear)
	{
		pthread_mutex_destroy(array_forks_mutex + i);
		i++;
	}
	free(array_forks_mutex);
	return ;
}
