#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_data
{
	int				count;
	pthread_mutex_t	mutex;
}	t_data;

void	*my_func(void *p_data)
{
	int	ret;
	for (int i = 0; i < 1000000; i ++)
	{
		ret = pthread_mutex_lock(&((t_data *)p_data)->mutex);
		if (ret != 0)
		{
			printf("pthread_mutex_lock : %s\n", strerror(ret));
			// return somehting ?
		}
		((t_data *)p_data)->count += 1;
		ret = pthread_mutex_unlock(&((t_data *)p_data)->mutex);
		if (ret != 0)
		{
			printf("pthread_mutex_lock : %s\n", strerror(ret));
			// return somehting ?
		}
	}
	return (NULL);
}

int	main(void)
{
	int			final_ret;
	int			nb_thread;
	int			ret;
	t_data		data;
	pthread_t	*ts;

	final_ret = 0;
	nb_thread = 5;
	data.count = 0;
	ret = pthread_mutex_init(&data.mutex, NULL);
	if (ret != 0)
	{
		printf("pthread_mutex_init : %s\n", strerror(ret));
		return (1);
	}
	ts = malloc(sizeof(pthread_t) * nb_thread);
	if (ts == NULL)
	{
		printf("malloc : %s\n", strerror(ret));
		pthread_mutex_destroy(&data.mutex);
		return (1);
	}
	for (int i = 0; i < nb_thread; i++)
	{
		ret = pthread_create(ts + i, NULL, my_func, &data);
		if (ret != 0)
		{
			printf("pthread_create : %s\n", strerror(ret));
			for (int j = 0; j < i; i++)
			{
				ret = pthread_join(ts[i], NULL);
				if (ret != 0)
				{
					printf("pthread_join : %s\n", strerror(ret));
				}
			}
			ret = pthread_mutex_destroy(&data.mutex);
			if (ret != 0)
			{
				printf("pthread_mutex_destroy : %s\n", strerror(ret));
			}
			free(ts);
		}
	}
	for (int i = 0; i < nb_thread; i++)
	{
		ret = pthread_join(ts[i], NULL);
		if (ret != 0)
		{
			final_ret = 1;
			printf("pthread_join : %s\n", strerror(ret));
		}
	}
	ret = pthread_mutex_destroy(&data.mutex);
	if (ret != 0)
	{
		printf("pthread_mutex_destroy : %s\n", strerror(ret));
		final_ret = 1;
	}
	free(ts);
	if (final_ret == 0)
		printf("count = %i\n", data.count);
	return (final_ret);
}
