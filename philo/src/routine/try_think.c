/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_think.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:36:13 by jweber            #+#    #+#             */
/*   Updated: 2025/08/27 18:57:12 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "routine.h"
#include "utils.h"
#include <unistd.h>

int	try_think(t_philo *p_philo, int *p_stop)
{
	long long	think_start_time;
	int			ret;

	// should check no philo as died here ? Necessary ?
	ret = ft_get_time(&think_start_time);
	if (ret != 0)
	{
		// also say other thread this thread has died
		// free forks ?
		*p_stop = TRUE;
		return (ret);
	}
	ret = print_message_philo(p_philo->p_printf_mutex,
			think_start_time - p_philo->ref_time,
			p_philo->philo_id, "is thinking");
	if (ret != 0)
	{
		// also say other thread this thread has died
		// free forks ?
		*p_stop = TRUE;
		return (ret);
	}
	return (SUCCESS);
}
