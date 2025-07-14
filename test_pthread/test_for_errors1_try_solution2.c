#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "ft_io.h"

#define NB_MUTEX 3
#define NB_THREAD 8

typedef struct s_data
{
	int				*p_val;
	pthread_mutex_t	*p_mutex_val;
}	t_data;


void	*routine(void *args)
{
	int		ret;
	int		have_locked;
	t_data 	*datas;

	datas = args;
	have_locked = 0;
	for (int i = 0; i < NB_MUTEX;	i++)
	{
		if (have_locked == 0)
		{
			ret = pthread_mutex_trylock(datas[i].p_mutex_val);
			if (ret == 0)
			{
				have_locked = 1;
				ft_printf_fd(1, "locked mutex with data.val = %i\n", *(datas[i].p_val));
				sleep(1);
				ret = pthread_mutex_unlock(datas[i].p_mutex_val);
				if (ret != 0)
					ft_printf_fd(1, "pthread_mutex_unlock : %s\n", strerror(ret));
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
	int				ret;
	pthread_t		ts[NB_THREAD];
	int				val_ref[NB_MUTEX];
	pthread_mutex_t	mutex_ref[NB_MUTEX];
	t_data			datas[NB_THREAD][NB_MUTEX];


	/*
	ft_printf_fd(1, "datas = %p\n", datas);
	ft_printf_fd(1, "&datas[0] = %p\n", &datas[0]);
	ft_printf_fd(1, "&datas[0].val = %p\n", &datas[0].val);
	ft_printf_fd(1, "&datas[1] = %p\n", &datas[1]);
	ft_printf_fd(1, "&datas[1].val = %p\n", &datas[1].val);
	ft_printf_fd(1, "&datas[2] = %p\n", &datas[2]);
	ft_printf_fd(1, "&datas[2].val = %p\n", &datas[2].val);
	*/
	for (int i = 0; i < NB_MUTEX; i++)
	{
		val_ref[i] = i + 1;
	}
	for (int i = 0; i < NB_MUTEX; i++)
	{
		ret = pthread_mutex_init(&(mutex_ref[i]), NULL);
		if (ret != 0)
			ft_printf_fd(1, "pthread_mutex_init : %s\n", strerror(ret));
	}
	for (int i = 0; i < NB_THREAD; i++)
	{
		for (int j = 0; j < NB_MUTEX; j++)
		{
			datas[i][j].p_val = val_ref + j;
			datas[i][j].p_mutex_val = mutex_ref + j;
		}
	}
	for (int i = 0; i < NB_THREAD; i++)
	{
		ret = pthread_create(ts + i, NULL, &routine, datas[i]);
		if (ret != 0)
			ft_printf_fd(1, "pthread_create : %s\n", strerror(ret));
		
	}
	for (int i = 0; i < NB_THREAD; i++)
	{
		ret = pthread_join(ts[i], NULL);
		if (ret != 0)
			ft_printf_fd(1, "pthread_create : %s\n", strerror(ret));
		
	}
	for (int i = 0; i < NB_MUTEX; i++)
	{
		ret = pthread_mutex_destroy(&mutex_ref[i]);
		if (ret != 0)
			ft_printf_fd(1, "pthread_mutex_destroy : %s\n", strerror(ret));
	}
}
