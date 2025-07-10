#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define NB_THREAD 4

void	*my_func(void *a)
{
	int	ret;

	ret = pthread_mutex_trylock(a);
	if (ret != 0)
		printf("pthread_mutex_lock : %s\n", strerror(ret));
	else
	{
		printf("mutex has been lock successfully\n");
		sleep(1);
		ret = pthread_mutex_unlock(a);
		if (ret != 0)
			printf("pthread_mutex_unlock : %s\n", strerror(ret));
		else
			printf("mutex has been unlock successfully\n");
	}
	return (NULL);
}

int	main(void)
{
	int				final_ret;
	int				ret;
	pthread_t		ts[NB_THREAD];
	pthread_mutex_t	mutex;

	ret = pthread_mutex_init(&mutex, NULL);
	if (ret != 0)
	{
		printf("pthread_mutex_init : %s\n", strerror(ret));
		return (1);
	}
	for (int i = 0; i < NB_THREAD; i++)
	{
		ret = pthread_create(ts + i, NULL, &my_func, &mutex);
		if (ret != 0)
		{
			printf("pthread_create : %s\n", strerror(ret));
			ret = pthread_mutex_destroy(&mutex);
			if (ret != 0)
				printf("pthread_mutex_destroy : %s\n", strerror(ret));
			for (int j = 0; j < i; j++)
			{
				ret = pthread_join(ts[j], NULL);
				if (ret != 0)
					printf("pthread_join : %s\n", strerror(ret));
			}
			return (1);
		}
	}
	final_ret = 0;
	for (int i = 0; i < NB_THREAD; i++)
	{
		ret = pthread_join(ts[i], NULL);
		if (ret != 0)
		{
			printf("pthread_join : %s\n", strerror(ret));
			final_ret = 1;
		}
		else
			printf("thread joined successfully\n");
	}
	ret = pthread_mutex_destroy(&mutex);
	if (ret != 0)
	{
		printf("pthread_mutex_destroy here : %s\n", strerror(ret));
		final_ret = 1;
	}
	return (final_ret);
}
