/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message_philo.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:22:48 by jweber            #+#    #+#             */
/*   Updated: 2025/08/21 14:31:22 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"
#include <stdio.h>

int	print_message_philo(t_philo *p_philo, char *str)
{
	int			ret;
	long long	time;

	ret = ft_get_time(&time);
	if (ret != 0)
	{
		// do stuff 
		return (ret);
	}
	ret = pthread_mutex_lock(p_philo->p_printf_mutex);
	if (ret != 0)
		return (ret);
	if (printf("%lld %i %s\n", time, p_philo->philo_id, str) < 0)
		return (ERROR_WRITE);
	pthread_mutex_unlock(p_philo->p_printf_mutex);
	return (SUCCESS);
}
