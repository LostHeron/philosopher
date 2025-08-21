/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:07:59 by jweber            #+#    #+#             */
/*   Updated: 2025/08/21 14:14:45 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdlib.h>

int	ft_get_time(long long *p_time)
{
	int				ret;
	struct timeval	tv;

	ret = gettimeofday(&tv, NULL);
	if (ret < 0)
	{
		return (ret);
	}
	*p_time = tv.tv_sec * 1000000;
	*p_time += tv.tv_usec;
	return (0);
}
