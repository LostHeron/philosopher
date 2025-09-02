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
void	ft_strcat_str(char *buf, size_t *p_buf_len, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		buf[*p_buf_len] = src[i];
		(*p_buf_len)++;
		i++;
	}
	return ;
}
