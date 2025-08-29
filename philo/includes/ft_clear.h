/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:20:29 by jweber            #+#    #+#             */
/*   Updated: 2025/08/20 17:21:08 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CLEAR_H
# define FT_CLEAR_H

# include <pthread.h>

void	clear_mutex(pthread_mutex_t *array_forks_mutex, int nb_to_clear);

#endif
