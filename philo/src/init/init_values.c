/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:54:49 by jweber            #+#    #+#             */
/*   Updated: 2025/09/01 13:09:45 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

static int	check_values(int nb_arg, t_simu_stat *p_simu_stat);
static int	last_check(int nb_arg, t_simu_stat *p_simu_stat);

int	init_values(int nb_arg, char **argv, t_simu_stat *p_simu_stat)
{
	int	ret;

	ret = ft_atoi_safe(argv[0], &p_simu_stat->nb_philos);
	if (ret != 0)
		return (print_error_atoi_safe(ret));
	ret = ft_atoi_safe(argv[1], &p_simu_stat->time_to_die);
	if (ret != 0)
		return (print_error_atoi_safe(ret));
	ret = ft_atoi_safe(argv[2], &p_simu_stat->time_to_eat);
	if (ret != 0)
		return (print_error_atoi_safe(ret));
	ret = ft_atoi_safe(argv[3], &p_simu_stat->time_to_sleep);
	if (ret != 0)
		return (print_error_atoi_safe(ret));
	if (nb_arg == 5)
	{
		ret = ft_atoi_safe(argv[4], &p_simu_stat->nb_time_each_one_eats);
		if (ret != 0)
			return (print_error_atoi_safe(ret));
	}
	else
		p_simu_stat->nb_time_each_one_eats = -1;
	return (check_values(nb_arg, p_simu_stat));
}

static int	check_values(int nb_arg, t_simu_stat *p_simu_stat)
{
	if (p_simu_stat->nb_philos <= 0)
	{
		ft_putstr_fd("nb_philo must be strictly greater than 0\n", 2);
		return (FAILURE);
	}
	if (p_simu_stat->time_to_die < 0)
	{
		ft_putstr_fd("time_to_die can not be negative\n", 2);
		return (FAILURE);
	}
	if (p_simu_stat->time_to_eat < 0)
	{
		ft_putstr_fd("time_to_eat can not be negative\n", 2);
		return (FAILURE);
	}
	if (p_simu_stat->time_to_sleep < 0)
	{
		ft_putstr_fd("time_to_sleep can not be negative\n", 2);
		return (FAILURE);
	}
	return (last_check(nb_arg, p_simu_stat));
}

static int	last_check(int nb_arg, t_simu_stat *p_simu_stat)
{
	if (nb_arg == 5 && p_simu_stat->nb_time_each_one_eats < 0)
	{
		ft_putstr_fd("nb_time_each_philo_must_eat can not be negative\n", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}
