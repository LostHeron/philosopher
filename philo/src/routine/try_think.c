/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_think.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:36:13 by jweber            #+#    #+#             */
/*   Updated: 2025/09/02 19:54:13 by jweber           ###   ########.fr       */
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

	ret = ft_get_time(&think_start_time);
	if (ret != 0)
	{
		*p_stop = TRUE;
		return (ret);
	}
	ret = print_message_philo(p_philo,
			think_start_time - p_philo->ref_time,
			"is thinking");
	if (ret != 0)
	{
		*p_stop = TRUE;
		return (ret);
	}
	return (SUCCESS);
}
