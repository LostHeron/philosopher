#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define NB_MUTEX 3
#define NB_THREAD 8

typedef struct s_data
{
	int				val[NB_MUTEX];
	pthread_mutex_t	mutex_val[NB_MUTEX];
}	t_data;

void	*routine(void *args)
{
	int		ret;
	int		have_locked;
	t_data 	*p_data;

	p_data = args;
	have_locked = 0;
	for (int i = 0; i < NB_MUTEX;	i++)
	{
		if (have_locked == 0)
		{
			ret = pthread_mutex_trylock(p_data->mutex_val + i);
			if (ret == 0)
			{
				have_locked = 1;
				printf("locked mutex with data.val = %i\n", p_data->val[i]);
				sleep(1);
				ret = pthread_mutex_unlock(p_data->mutex_val + i);
				if (ret != 0)
					printf("pthread_mutex_unlock : %s\n", strerror(ret));
			}
		}
	}
	if (have_locked == 0)
		printf("thread could not lock any !\n");
	else
		printf("this thread have locked some !\n");
	return (NULL);
}

int	main(void)
{
	int		ret;
	pthread_t	ts[NB_THREAD];
	t_data	data;

	for (int i = 0; i < NB_MUTEX; i++)
	{
		data.val[i] = i + 1;
	}
	for (int i = 0; i < NB_MUTEX; i++)
	{
		ret = pthread_mutex_init(data.mutex_val + i, NULL);
		if (ret != 0)
			printf("pthread_mutex_init : %s\n", strerror(ret));
	}
	for (int i = 0; i < NB_THREAD; i++)
	{
		ret = pthread_create(ts + i, NULL, &routine, &data);
		if (ret != 0)
			printf("pthread_create : %s\n", strerror(ret));
		
	}
	for (int i = 0; i < NB_THREAD; i++)
	{
		ret = pthread_join(ts[i], NULL);
		if (ret != 0)
			printf("pthread_create : %s\n", strerror(ret));
		
	}
	for (int i = 0; i < NB_MUTEX; i++)
	{
		ret = pthread_mutex_destroy(data.mutex_val + i);
		if (ret != 0)
			printf("pthread_mutex_destroy : %s\n", strerror(ret));
	}
}
