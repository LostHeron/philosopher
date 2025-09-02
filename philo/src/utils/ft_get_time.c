/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:07:59 by jweber            #+#    #+#             */
/*   Updated: 2025/09/02 17:40:57 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "philo.h"
#include "utils.h"
#include <stdlib.h>

/* This function should put the current time from Epoch (1970-01-01 00:00:00
 * +0000 (UTC).) in millisecond (ms) in the variable passed
 * by reference (p_time).
 * If gettimeofday fail, return 1;
 * else return success !
*/
int	ft_get_time(long long *p_time)
{
	int				ret;
	struct timeval	tv;

	ret = gettimeofday(&tv, NULL);
	if (ret < 0)
	{
		ft_putstr_fd("gettimeofday failure\n", 2);
		return (ret);
	}
	*p_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (SUCCESS);
}
