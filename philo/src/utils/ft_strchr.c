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

/*
#include <string.h>
#include <stdio.h>

int	main(void)
{
	char				*s;
	char				to_find;
	char				tmp;
	unsigned long long	addr_init;
	unsigned long long	addr_res_or;
	unsigned long long	addr_res_ft;

	s = "tripouille";
	to_find = 't';
	tmp = to_find;
	printf("to_find = %i\n", tmp);
	tmp = to_find + 100;
	printf("to_find + 256 = %i\n", tmp);
	addr_init = (unsigned long long) s;
	addr_res_ft = (unsigned long long) ft_strchr(s, to_find + 256);
	addr_res_or = (unsigned long long) strchr(s, to_find + 256);
	printf("addr_init	= %llu\n", addr_init);
	printf("addr_res_ft	= %llu\n", addr_res_ft);
	printf("addr_res_or	= %llu\n", addr_res_or);
}
*/
