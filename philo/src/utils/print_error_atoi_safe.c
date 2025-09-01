/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_atoi_safe.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 12:02:24 by jweber            #+#    #+#             */
/*   Updated: 2025/09/01 12:15:18 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	print_error_atoi_safe(int err)
{
	if (err == ATOI_SAFE_TOO_LARGE_INPUT)
		ft_putstr_fd("input is too long\n", 2);
	else if (err == ATOI_SAFE_WRONG_INPUT)
		ft_putstr_fd("wrong input\n", 2);
	else if (err == ATOI_SAFE_OVERFLOW)
		ft_putstr_fd("input will overflow\n", 2);
	else if (err == ATOI_SAFE_UNDERFLOW)
		ft_putstr_fd("input will underflow\n", 2);
	return (err);
}
