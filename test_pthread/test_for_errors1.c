#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "ft_io.h"

#define NB_MUTEX 3
#define NB_THREAD 8

typedef struct s_data
{
	int				val;
	pthread_mutex_t	mutex_val;
}	t_data;


void	*routine(void *args)
{
	int		ret;
	int		have_locked;
	const t_data 	*datas;

	datas = args;
	have_locked = 0;
	for (int i = 0; i < NB_MUTEX;	i++)
	{
		if (have_locked == 0)
		{
			ret = pthread_mutex_trylock((pthread_mutex_t *)&datas[i].mutex_val);
			if (ret == 0)
			{
				have_locked = 1;
				ft_printf_fd(1, "locked mutex with data.val = %i\n", datas[i].val);
				sleep(1);
				ret = pthread_mutex_unlock((pthread_mutex_t *)&datas[i].mutex_val);
				if (ret != 0)
					printf("pthread_mutex_unlock : %s\n", strerror(ret));
			}
		}
	}
	if (have_locked == 0)
		ft_printf_fd(1, "thread could not lock any !\n");
	else
		ft_printf_fd(1, "this thread have locked some !\n");
	return (NULL);
}

int	main(void)
{
	int		ret;
	pthread_t	ts[NB_THREAD];
	t_data	datas[NB_MUTEX];

	printf("datas = %p\n", datas);
	printf("&datas[0] = %p\n", &datas[0]);
	printf("&datas[0].val = %p\n", &datas[0].val);
	printf("&datas[1] = %p\n", &datas[1]);
	printf("&datas[1].val = %p\n", &datas[1].val);
	printf("&datas[2] = %p\n", &datas[2]);
	printf("&datas[2].val = %p\n", &datas[2].val);
	for (int i = 0; i < NB_MUTEX; i++)
	{
		datas[i].val = i + 1;
	}
	for (int i = 0; i < NB_MUTEX; i++)
	{
		ret = pthread_mutex_init(&datas[i].mutex_val, NULL);
		if (ret != 0)
			printf("pthread_mutex_init : %s\n", strerror(ret));
	}
	for (int i = 0; i < NB_THREAD; i++)
	{
		ret = pthread_create(ts + i, NULL, &routine, datas);
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
		ret = pthread_mutex_destroy(&datas[i].mutex_val);
		if (ret != 0)
			printf("pthread_mutex_destroy : %s\n", strerror(ret));
	}
}
