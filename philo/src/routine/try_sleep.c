/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_sleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:19:48 by jweber            #+#    #+#             */
/*   Updated: 2025/08/21 14:35:55 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "routine.h"
#include <unistd.h>

int	try_sleep(t_philo *p_philo)
{
	int			ret;

	ret = print_message_philo(p_philo, "is sleeping");
	if (ret != 0)
		return (ret);
	usleep(p_philo->time_to_sleep);
	return (0);
}
