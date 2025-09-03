/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:27:45 by jweber            #+#    #+#             */
/*   Updated: 2025/09/03 11:25:33 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>

enum	e_atoi_safe
{
	ATOI_SAFE_OVERFLOW = 1,
	ATOI_SAFE_UNDERFLOW,
	ATOI_SAFE_WRONG_INPUT,
	ATOI_SAFE_TOO_LARGE_INPUT,
};

int		ft_atoi_safe(const char *str, int *p_value);

int		print_error_atoi_safe(int err);
int		ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);
int		ft_isspace(char c);
char	*ft_strchr(const char *s, int c);
int		ft_get_time(long long *p_time);
void	ft_strcat_nb(char *buf, size_t *p_buf_len, long long nb);
void	ft_strcat_str(char *buf, size_t *p_buf_len, const char *src);
int		usleep_failure(void);

#endif
