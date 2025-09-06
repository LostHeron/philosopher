/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_buffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 23:10:41 by jweber            #+#    #+#             */
/*   Updated: 2025/09/06 23:11:13 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "philo.h"

void	prepare_buffer(t_philo *p_philo, long long time, char *str)
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
