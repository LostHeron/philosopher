/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:54:49 by jweber            #+#    #+#             */
/*   Updated: 2025/08/20 17:03:47 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"
#include <stdio.h>

static int	check_values(int nb_arg, t_philo_stat *p_philo_stat);
static int	last_check(int nb_arg, t_philo_stat *p_philo_stat);

int	init_values(int nb_arg, char **argv, t_philo_stat *p_philo_stat)
{
	p_philo_stat->nb_philo = ft_atoi(argv[0]);
	p_philo_stat->time_to_die = ft_atoi(argv[1]);
	p_philo_stat->time_to_eat = ft_atoi(argv[2]);
	p_philo_stat->time_to_sleep = ft_atoi(argv[3]);
	if (nb_arg == 5)
		p_philo_stat->nb_time_each_one_eats = ft_atoi(argv[4]);
	else
		p_philo_stat->nb_time_each_one_eats = -1;
	return (check_values(nb_arg, p_philo_stat));
}

static int	check_values(int nb_arg, t_philo_stat *p_philo_stat)
{
	if (p_philo_stat->nb_philo <= 0)
	{
		printf("nb_philo must be strictly greater than 0\n");
		return (FAILURE);
	}
	if (p_philo_stat->time_to_die < 0)
	{
		printf("time_to_die can not be negative\n");
		return (FAILURE);
	}
	if (p_philo_stat->time_to_eat < 0)
	{
		printf("time_to_eat can not be negative\n");
		return (FAILURE);
	}
	if (p_philo_stat->time_to_sleep < 0)
	{
		printf("time_to_sleep can not be negative\n");
		return (FAILURE);
	}
	return (last_check(nb_arg, p_philo_stat));
}

static int	last_check(int nb_arg, t_philo_stat *p_philo_stat)
{
	if (nb_arg == 5 && p_philo_stat->nb_time_each_one_eats < 0)
	{
		printf("nb_time_each_philo_must_eat can not be negative\n");
		return (FAILURE);
	}
	return (SUCCESS);
}
