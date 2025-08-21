/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 13:37:28 by jweber            #+#    #+#             */
/*   Updated: 2025/08/21 14:40:03 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROUTINE_H
# define ROUTINE_H

# include "philo.h"

void	*routine(void *args);
int		print_message_philo(t_philo *p_philo, char *str);
int		try_eat(t_philo *p_philo);
int		try_sleep(t_philo *p_philo);
int		try_think(t_philo *p_philo);

#endif
