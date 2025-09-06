/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_to_shift_even_philos.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:15:20 by jweber            #+#    #+#             */
/*   Updated: 2025/09/04 17:47:38 by jweber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"
#include "routine.h"
#include <unistd.h>

static int	check_finished_waiting(long long wait_start_time,
				int *p_done_eating, int time_to_wait);

/* to check
 *	-> usleep fail : DONE -> OK !
 *	-> check_death fail : DONE -> OK !
 *	-> check_finished_waiting : DONE -> OK !
*/
int	wait_to_shift_even_philos(t_philo *p_philo, int *p_stop,
				long long last_meal, long long time_to_wait)
{
	int	ret;
	int	done_waiting;
	int	is_dead;

	ret = SUCCESS;
	done_waiting = FALSE;
	while (ret == SUCCESS && done_waiting == FALSE)
	{
		if (usleep(OPERATION_STEP) < 0)
			return (usleep_failure());
		ret = check_death(p_philo, last_meal, &is_dead);
		if (ret != 0 || is_dead == TRUE)
		{
			*p_stop = TRUE;
			return (ret);
		}
		ret = check_finished_waiting(last_meal, &done_waiting,
				time_to_wait);
	}
	return (SUCCESS);
}

static int	check_finished_waiting(long long wait_start_time,
				int *p_done_eating, int time_to_wait)
{
	long long	current_time;
	int			ret;

	ret = ft_get_time(&current_time);
	if (ret != SUCCESS)
	{
		return (ret);
	}
	if (current_time - wait_start_time >= time_to_wait)
	{
		*p_done_eating = TRUE;
	}
	return (SUCCESS);
}
