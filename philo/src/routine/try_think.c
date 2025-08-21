/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_think.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:36:13 by jweber            #+#    #+#             */
/*   Updated: 2025/08/21 14:42:03 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "routine.h"
#include <unistd.h>

int	try_sleep(t_philo *p_philo)
{
	int			ret;

	ret = print_message_philo(p_philo, "is thinking");
	if (ret != 0)
		return (ret);
	return (0);
}
