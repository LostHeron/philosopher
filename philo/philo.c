/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:41:26 by jweber            #+#    #+#             */
/*   Updated: 2025/09/01 15:11:23 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "ft_init.h"
#include "execution.h"
#include "ft_clear.h"
#include "utils.h"

int	main(int argc, char **argv)
{
	int			ret;
	t_simu_stat	simu_stat;
	t_mutexes	mutexes;
	t_philo		*arr_philo;

	if (argc < 5 || argc > 6)
	{
		ft_putstr_fd("usage : ./philo	number_of_philosophers "
			"time_to_die time_to_eat time_to_sleep "
			"[number_of_times_each_philosopher_must_eat]\n", 2);
		return (1);
	}
	ret = init_values(argc - 1, argv + 1, &simu_stat);
	if (ret != SUCCESS)
		return (FAILURE);
	ret = init_philos(simu_stat, &mutexes, &arr_philo);
	if (ret != 0)
	{
		ft_putstr_fd("failed to init different structures\n", 2);
		return (ret);
	}
	ret = start_simulation(simu_stat, &arr_philo);
	clear_all(&mutexes, &arr_philo, simu_stat.nb_philos);
	return (ret);
}
