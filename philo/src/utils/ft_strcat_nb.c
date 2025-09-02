/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat_nb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:01:10 by jweber            #+#    #+#             */
/*   Updated: 2025/09/02 11:47:52 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/* This function should concatenate nb as string to the end of the buffer
*/
void	ft_strcat_nb(char *buf, size_t *p_buf_len, long long nb)
{
	if (nb > 9)
	{
		ft_strcat_nb(buf, p_buf_len, nb / 10);
	}
	buf[*p_buf_len] = nb % 10 + '0';
	(*p_buf_len)++;
	return ;
}
