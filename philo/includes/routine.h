/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 13:37:28 by jweber            #+#    #+#             */
/*   Updated: 2025/09/04 17:32:08 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROUTINE_H
# define ROUTINE_H

# include "philo.h"

void	*routine(void *args);
int		wait_to_shift_even_philos(t_philo *p_philo, int *p_stop,
			long long last_meal, long long time_to_wait);
int		print_message_philo(t_philo *p_philo, long long time, char *str);
int		print_message_philo_no_check(t_philo *p_philo, long long time,
			char *str);
int		print_message_philo_eating(t_philo *p_philo, int *p_nb_time_eaten,
			long long time, char *str);
int		try_eat(t_philo *p_philo, long long *p_last_meal, int *p_stop,
			int *p_nb_time_eaten);
int		try_take_forks(t_philo *p_philo, int *p_can_eat,
			int *p_right_fork_locked, int *p_left_fork_locked);
int		eat(t_philo *p_philo, long long *p_last_meal, int *p_stop,
			int *p_nb_time_eaten);
int		try_sleep(t_philo *p_philo, long long last_meal, int *p_stop);
int		try_think(t_philo *p_philo, int *p_stop);
int		check_death(t_philo *p_philo, long long last_meal, int *p_has_died);
int		try_kill_philo(pthread_mutex_t *p_stop_exec_mutex, int *p_stop_exec,
			t_philo *p_philo);

#endif
