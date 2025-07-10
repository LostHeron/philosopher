#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void	*my_func(void *param)
{
	(void) param;
	sleep(1);
	printf("coucou la team\n");
	sleep(2);
	printf("on a attendu 2 seconde \n");
	return (NULL);
}

int	main(void)
{
	int			ret;
	int			final_ret;
	pthread_t	t1;
	pthread_t	t2;

	final_ret = 0;
	ret = pthread_create(&t1, NULL, &my_func, NULL);
	if (ret != 0)
	{
		dprintf(2, "%s\n", strerror(ret));
		return (1);
	}
	ret = pthread_create(&t2, NULL, &my_func, NULL);
	if (ret != 0)
	{
		dprintf(2, "%s\n", strerror(ret));
		ret = pthread_join(t1, NULL);
		if (ret != 0)
		{
			dprintf(2, "%s\n", strerror(ret));
		}
		return (1);
	}
	/*
	program with no multithreading !
	my_func();
	my_func();
	return (0);
	*/
	ret = pthread_join(t1, NULL);
	if (ret != 0)
	{
		dprintf(2, "%s\n", strerror(ret));
		final_ret = ret;
	}
	ret = pthread_join(t2, NULL);
	if (ret != 0)
	{
		dprintf(2, "%s\n", strerror(ret));
		final_ret = ret;
	}
	return (final_ret);
}
