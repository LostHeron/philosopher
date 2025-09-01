/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:56:25 by jweber            #+#    #+#             */
/*   Updated: 2025/09/01 13:10:53 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_INIT_H
# define FT_INIT_H

# include "philo.h"

int	init_values(int nb_arg, char **argv, t_simu_stat *p_simu_stat);
int	init_philos(t_simu_stat simu_stat, t_mutexes *p_mutexes,
		t_philo **p_arr_philo);
int	init_mutexes(int nb_philo, t_mutexes *p_mutexes);
int	init_arr_philo(t_simu_stat simu_stat,
		t_mutexes mutexes, t_philo **p_arr_philo);

#endif
