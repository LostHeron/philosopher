
#include <stdio.h>
#include <pthread.h>
#include <string.h>

typedef struct s_data
{
	pthread_mutex_t mutex;
	int	count;
} t_data;

void	*my_func(void *p_data)
{
	int	ret;

	for (int i = 0; i < 1000000; i++)
	{
		(void) ret;
		pthread_mutex_lock(&((t_data *)p_data)->mutex);
		((t_data *)p_data)->count += 1;
		pthread_mutex_unlock(&((t_data *)p_data)->mutex);
		/*
		ret = pthread_mutex_lock(&((t_data *)p_data)->mutex);
		if (ret != 0)
		{
			printf("%s\n", strerror(ret));
			// return (address of something);
		}
		else 
		{
			((t_data *)p_data)->count += 1;
			ret = pthread_mutex_unlock(&((t_data *)p_data)->mutex);
			if (ret != 0)
			{
				printf("%s\n", strerror(ret));
				// return (address of something);
			}
		}
		*/
	}
	return (NULL);
}

int	main(void)
{
	t_data		data;
	int			ret;
	int			final_ret;
	pthread_t	t1;
	pthread_t	t2;
	
	data.count = 0;
	ret = pthread_mutex_init(&data.mutex, NULL);
	if (ret != 0)
	{
		printf("%s\n", strerror(ret));
		return (1);
	}
	final_ret = 0;
	ret = pthread_create(&t1, NULL, &my_func, &data);
	if (ret != 0)
	{
		printf("%s\n", strerror(ret));
		ret = pthread_mutex_destroy(&data.mutex);
		if (ret != 0)
			printf("%s\n", strerror(ret));
		return (1);
	}
	ret = pthread_create(&t2, NULL, &my_func, &data);
	if (ret != 0)
	{
		printf("%s\n", strerror(ret));
		ret = pthread_join(t1, NULL);
		if (ret != 0)
			printf("%s\n", strerror(ret));
		ret = pthread_mutex_destroy(&data.mutex);
		if (ret != 0)
			printf("%s\n", strerror(ret));
		return (1);
	}
	ret = pthread_join(t1, NULL);
	if (ret != 0)
	{
		printf("%s\n", strerror(ret));
		final_ret = 1;
	}
	ret = pthread_join(t2, NULL);
	if (ret != 0)
	{
		printf("%s\n", strerror(ret));
		final_ret = 1;
	}
	ret = pthread_mutex_destroy(&data.mutex);
	if (ret != 0)
	{
		printf("%s\n", strerror(ret));
		final_ret = 1;
	}
	printf("count = %i\n", data.count);
	return (final_ret);
}
