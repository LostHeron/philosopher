/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 11:47:55 by jweber            #+#    #+#             */
/*   Updated: 2025/08/29 12:11:39 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHITE_SPACE
# define WHITE_SPACE " \f\n\r\t\v"
#endif
#include "utils.h"
#include <stdlib.h>

/* checks for white-space characters.  In the "C" and "POSIX" locales, 
 * these are: 
 * - space (' '), 
 * - form-feed ('\f'), 
 * - newline ('\n'), 
 * - carriage return ('\r'), 
 * - horizontal tab ('\t'),  
 * - vertical tab ('\v').
*/
int	ft_isspace(char c)
{
	return (ft_strchr(WHITE_SPACE, c) != NULL);
}
