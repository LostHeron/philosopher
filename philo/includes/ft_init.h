/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:56:25 by jweber            #+#    #+#             */
/*   Updated: 2025/08/27 18:45:03 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_INIT_H
# define FT_INIT_H

# include "philo.h"

int	init_values(int nb_arg, char **argv, t_philo_stat *p_philo_stat);
int	init_forks(int nb_philo, t_forks *p_forks);
int	init_arr_philo(t_philo_stat philo_stat,
		t_forks forks, t_philo **p_arr_philo);

#endif
