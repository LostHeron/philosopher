/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_mutex_lock_failure.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 19:54:25 by jweber            #+#    #+#             */
/*   Updated: 2025/09/04 19:55:10 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	pthread_mutex_lock_failure(int ret)
{
	ft_putstr_fd("pthread_mutex_lock failed\n", 2);
	return (ret);
}
