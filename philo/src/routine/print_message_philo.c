/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message_philo.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:22:48 by jweber            #+#    #+#             */
/*   Updated: 2025/09/04 17:29:57 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "routine.h"
#include "utils.h"
#include <unistd.h>

static void	prepare_buffer(t_philo *p_philo, long long time, char *str);

int	print_message_philo(t_philo *p_philo, long long time, char *str)
{
	int	ret;

	prepare_buffer(p_philo, time, str);
	ret = pthread_mutex_lock(p_philo->p_stop_exec_mutex);
	if (ret != 0)
		return (pthread_mutex_lock_failure(ret));
	if (*p_philo->p_stop_exec == FALSE)
	{
		ret = write(1, p_philo->buf_msg, p_philo->buf_msg_len);
	}
	pthread_mutex_unlock(p_philo->p_stop_exec_mutex);
	if (ret < 0)
	{
		ft_putstr_fd("write failed\n", 2);
		return (FAILURE);
	}
	else
		return (SUCCESS);
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
