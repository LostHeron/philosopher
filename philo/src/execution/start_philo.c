/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:37:04 by jweber            #+#    #+#             */
/*   Updated: 2025/08/20 18:45:12 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "ft_init.h"

int	start_philo(t_philo_stat philo_stat)
{
	t_forks	forks;
	int		ret;

	ret = init_forks(philo_stat.nb_philo, &forks);
	if (ret != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
