/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:42:54 by jweber            #+#    #+#             */
/*   Updated: 2025/09/01 15:11:15 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "philo.h"

int	start_philos(t_simu_stat simu_stat, t_philo **p_arr_philo);
int	create_philos(pthread_t *arr_th_philo, t_simu_stat *p_simu_stat,
		t_philo *arr_philos, int *p_nb_th_launched);
int	join_philos(pthread_t *arr_th_philo, pthread_mutex_t *p_printf_mutex,
		int nb_to_join);

#endif
