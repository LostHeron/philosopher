/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:42:08 by jweber            #+#    #+#             */
/*   Updated: 2025/09/01 14:23:42 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "ft_clear.h"
#include <pthread.h>
#include <stdlib.h>

static int	init_array_forks(int **p_array_forks, int nb_philo);
static int	init_array_forks_mutex(pthread_mutex_t **p_array_forks_mutex,
				int nb_philo);
static int	init_other_mutex(t_mutexes *p_mutexes);

/*		This function should initialize the different forks 
 *	and init each mutex associated with the forks 
 *	to check : 
 *		-> init_array_forks fail : DONE -> OK !
 *		-> init_array_forks_mutex fail : DONE -> OK !
 *		-> init_other_mutex fail : DONE -> OK !
*/
int	init_mutexes(int nb_philo, t_mutexes *p_mutexes)
{
	int	ret;

	ret = init_array_forks(&p_mutexes->array_forks, nb_philo);
	if (ret != SUCCESS)
		return (ret);
	ret = init_array_forks_mutex(&p_mutexes->array_forks_mutex, nb_philo);
	if (ret != SUCCESS)
	{
		free(p_mutexes->array_forks);
		return (ret);
	}
	ret = init_other_mutex(p_mutexes);
	if (ret != SUCCESS)
	{
		free(p_mutexes->array_forks);
		clear_mutex(&p_mutexes->array_forks_mutex, nb_philo);
		return (ret);
	}
	return (SUCCESS);
}

/* to check
 *	-> malloc fail : DONE -> OK !
*/
static int	init_array_forks(int **p_array_forks, int nb_philo)
{
	int	i;

	*p_array_forks = malloc(nb_philo * sizeof(int));
	if (*p_array_forks == NULL)
		return (FAILURE);
	i = 0;
	while (i < nb_philo)
	{
		(*p_array_forks)[i] = AVAILABLE;
		i++;
	}
	return (SUCCESS);
}

/* to check
 *	-> malloc fail : DONE -> OK !
 *	-> pthread_mutex_init : DONE -> OK !
*/
static int	init_array_forks_mutex(pthread_mutex_t **p_array_forks_mutex,
					int nb_philo)
{
	int	i;
	int	ret;

	*p_array_forks_mutex = malloc(nb_philo * sizeof(pthread_mutex_t));
	if (*p_array_forks_mutex == NULL)
		return (FAILURE);
	i = 0;
	while (i < nb_philo)
	{
		ret = pthread_mutex_init((*p_array_forks_mutex) + i, NULL);
		if (ret != 0)
		{
			clear_mutex(p_array_forks_mutex, i);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

/* to check :
 *	-> first pthread_mutex_init fail : DONE -> OK !
 *	-> second pthread_mutex_init fail : DONE -> OK !
 *	-> third pthread_mutex_init fail : DONE -> OK !
*/
static int	init_other_mutex(t_mutexes *p_mutexes)
{
	int	ret;

	p_mutexes->stop_exec = FALSE;
	ret = pthread_mutex_init(&p_mutexes->stop_exec_mutex, NULL);
	if (ret != 0)
	{
		return (FAILURE);
	}
	p_mutexes->nb_finished_eaten = 0;
	ret = pthread_mutex_init(&p_mutexes->nb_finished_eaten_mutex, NULL);
	if (ret != 0)
	{
		pthread_mutex_destroy(&p_mutexes->stop_exec_mutex);
		return (FAILURE);
	}
	ret = pthread_mutex_init(&p_mutexes->start_mutex, NULL);
	if (ret != 0)
	{
		pthread_mutex_destroy(&p_mutexes->stop_exec_mutex);
		pthread_mutex_destroy(&p_mutexes->nb_finished_eaten_mutex);
		return (FAILURE);
	}
	return (SUCCESS);
}
