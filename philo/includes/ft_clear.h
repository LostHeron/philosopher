/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:20:29 by jweber            #+#    #+#             */
/*   Updated: 2025/09/01 13:00:43 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CLEAR_H
# define FT_CLEAR_H

# include "philo.h"
# include <pthread.h>

void	clear_mutex(pthread_mutex_t **p_array_forks_mutex, int nb_to_clear);
void	clear_all(t_mutexes *p_mutexes, t_philo **p_arr_philo, int nb_philo);

#endif
