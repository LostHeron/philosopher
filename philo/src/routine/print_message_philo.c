/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message_philo.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:22:48 by jweber            #+#    #+#             */
/*   Updated: 2025/08/27 18:41:30 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"
#include <stdio.h>

/* This function should print a message to screen
 * if an error occur (function call fail), it should return non-null integer
 * in case nothing happend bad it should return 0;
*/
int	print_message_philo(pthread_mutex_t *p_printf_mutex, long long time,
		int philo_id, char *str)
{
	int			ret;
	int			final_ret;

	ret = pthread_mutex_lock(p_printf_mutex);
	if (ret != 0)
		return (ret);
	final_ret = 0;
	if (printf("%lld philo nb_%i %s\n", time, philo_id, str) < 0)
		final_ret = ERROR_WRITE;
	pthread_mutex_unlock(p_printf_mutex);
	return (final_ret);
}
