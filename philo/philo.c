/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:41:26 by jweber            #+#    #+#             */
/*   Updated: 2025/08/20 18:43:26 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "ft_init.h"
#include "execution.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	int				ret;
	t_philo_stat	philo_stat;

	if (argc < 5 || argc > 6)
	{
		printf("usage : ./philo	number_of_philosophers "
			"time_to_die time_to_eat time_to_sleep "
			"[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	ret = init_values(argc - 1, argv + 1, &philo_stat);
	if (ret != SUCCESS)
		return (FAILURE);
	start_philo(philo_stat);
}
