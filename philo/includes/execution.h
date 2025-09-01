/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:42:54 by jweber            #+#    #+#             */
/*   Updated: 2025/09/01 13:10:24 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "philo.h"

int	start_philo(t_simu_stat simu_stat, t_philo **p_arr_philo);
int	launch_philo(t_simu_stat *p_simu_stat, t_philo *arr_philo);

#endif
