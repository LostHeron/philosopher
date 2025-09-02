/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message_philo_no_check.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:22:48 by jweber            #+#    #+#             */
/*   Updated: 2025/09/02 17:38:11 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"
#include <unistd.h>

int	print_message_philo_no_check(t_philo *p_philo, long long time, char *str)
{
	int	ret;

	p_philo->buf_msg[0] = '\0';
	p_philo->buf_msg_len = 0;
	ft_strcat_nb(p_philo->buf_msg, &p_philo->buf_msg_len, time);
	ft_strcat_str(p_philo->buf_msg, &p_philo->buf_msg_len, "\t");
	ft_strcat_nb(p_philo->buf_msg, &p_philo->buf_msg_len,
		p_philo->philo_id);
	ft_strcat_str(p_philo->buf_msg, &p_philo->buf_msg_len, "\t");
	ft_strcat_str(p_philo->buf_msg, &p_philo->buf_msg_len, str);
	ft_strcat_str(p_philo->buf_msg, &p_philo->buf_msg_len, "\n");
	ret = write(1, p_philo->buf_msg, p_philo->buf_msg_len);
	if (ret < 0)
	{
		ft_putstr_fd("write error !\n", 2);
		return (FAILURE);
	}
	else
		return (SUCCESS);
}
