/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message_philo_eating.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:22:48 by jweber            #+#    #+#             */
/*   Updated: 2025/09/04 17:59:53 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "routine.h"
#include "utils.h"
#include <unistd.h>

static void	prepare_buffer(t_philo *p_philo, long long time, char *str);
static int	check_all_philos_finish_eaten(t_philo *p_philo,
				int *p_nb_time_eaten);

int	print_message_philo_eating(t_philo *p_philo, int *p_nb_time_eaten,
		long long time, char *str)
{
	int	ret;

	prepare_buffer(p_philo, time, str);
	ret = pthread_mutex_lock(p_philo->p_stop_exec_mutex);
	if (ret != 0)
	{
		ft_putstr_fd("pthread_mutex_lock fail to lock printf mutex\n", 2);
		return (ret);
	}
	if (*p_philo->p_stop_exec == FALSE)
	{
		ret = write(1, p_philo->buf_msg, p_philo->buf_msg_len);
		if (ret < 0)
		{
			ft_putstr_fd("write error !\n", 2);
			return (FAILURE);
		}
	}
	ret = check_all_philos_finish_eaten(p_philo, p_nb_time_eaten);
	pthread_mutex_unlock(p_philo->p_stop_exec_mutex);
	return (ret);
}

static void	prepare_buffer(t_philo *p_philo, long long time, char *str)
{
	p_philo->buf_msg[0] = '\0';
	p_philo->buf_msg_len = 0;
	ft_strcat_nb(p_philo->buf_msg, &p_philo->buf_msg_len, time);
	ft_strcat_str(p_philo->buf_msg, &p_philo->buf_msg_len, "\t");
	ft_strcat_nb(p_philo->buf_msg, &p_philo->buf_msg_len,
		p_philo->philo_id);
	ft_strcat_str(p_philo->buf_msg, &p_philo->buf_msg_len, "\t");
	ft_strcat_str(p_philo->buf_msg, &p_philo->buf_msg_len, str);
	ft_strcat_str(p_philo->buf_msg, &p_philo->buf_msg_len, "\n");
}

static int	check_all_philos_finish_eaten(t_philo *p_philo,
				int *p_nb_time_eaten)
{
	int	ret;

	if (p_philo->nb_time_to_eat >= 0
		&& *p_nb_time_eaten >= p_philo->nb_time_to_eat
		&& p_philo->nb_finished_eaten_incremented == FALSE)
	{
		ret = pthread_mutex_lock(p_philo->p_nb_finished_eaten_mutex);
		if (ret != 0)
			return (ret);
		(*p_philo->p_nb_finished_eaten)++;
		p_philo->nb_finished_eaten_incremented = TRUE;
		if (*p_philo->p_nb_finished_eaten == p_philo->nb_philos)
		{
			*p_philo->p_stop_exec = TRUE;
		}
		pthread_mutex_unlock(p_philo->p_nb_finished_eaten_mutex);
	}
	return (SUCCESS);
}
