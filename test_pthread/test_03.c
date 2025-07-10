#include <stdio.h>
#include <pthread.h>
#include <string.h>

int	mail = 0;

void	*my_func(void *p_count)
{
	for (int i = 0; i < 1000000; i++)
	{
		*((int *)p_count) += 1;
	}
	return (NULL);
}

int	main(void)
{
	int			count;
	int			ret;
	int			final_ret;
	pthread_t	t1;
	pthread_t	t2;
	
	count = 0;
	final_ret = 0;
	ret = pthread_create(&t1, NULL, &my_func, &count);
	if (ret != 0)
	{
		printf("%s\n", strerror(ret));
		return (1);
	}
	ret = pthread_create(&t2, NULL, &my_func, &count);
	if (ret != 0)
	{
		printf("%s\n", strerror(ret));
		ret = pthread_join(t1, NULL);
		if (ret != 0)
		{
			printf("%s\n", strerror(ret));
		}
		return (1);
	}
	ret = pthread_join(t1, NULL);
	if (ret != 0)
	{
		final_ret = 1;
		printf("%s\n", strerror(ret));
	}
	ret = pthread_join(t2, NULL);
	if (ret != 0)
	{
		final_ret = 1;
		printf("%s\n", strerror(ret));
	}
	printf("count = %i\n", count);
	return (final_ret);
}
