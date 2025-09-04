/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:55:05 by jweber            #+#    #+#             */
/*   Updated: 2025/01/30 16:51:04 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	c_c;

	i = 0;
	c_c = c;
	while (s[i])
	{
		if (s[i] == c_c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == c_c)
		return ((char *)(s + i));
	return (NULL);
}
