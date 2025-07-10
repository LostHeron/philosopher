#include <pthread.h>
#include <string.h>
#include <stdio.h>

void	*addition(void *a)
{
	*((int *)a) += 2;
	return (NULL);
}

int	main(void)
{
	int			x;
	int			final_ret;
	int			ret;
	pthread_t	t1;
	pthread_t	t2;

	x = 0;
	final_ret = 0;
	printf("x before pthread call : %i\n", x);
	ret = pthread_create(&t1, NULL, addition, &x);
	if (ret != 0)
	{
		printf("%s\n", strerror(ret));
		return (1);
	}
	ret = pthread_create(&t2, NULL, addition, &x);
	if (ret != 0)
	{
		ret = pthread_join(t1, NULL);
		if (ret != 0)
		{
			printf("%s\n", strerror(ret));
			return (1);
		}
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
	printf("x after pthread call : %i\n", x);
	return (final_ret);
}
