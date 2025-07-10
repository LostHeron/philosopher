#include <pthread.h>
#include <stdio.h>
#include <string.h>

void	*my_func(void *a)
{
	*(int *)a = 20;
	return (a);
}

int	main(void)
{
	pthread_t	t1;
	int			x;
	int			ret;
	int			final_ret;
	int			*xx;

	final_ret = 0;
	(void) final_ret;
	x = 0;
	ret = pthread_create(&t1, NULL, &my_func, &x);
	if (ret != 0)
	{
		printf("pthread_create : %s\n", strerror(ret));
		return (1);
	}
	ret = pthread_join(t1, (void **)&xx);
	if (ret != 0)
	{
		printf("pthread_joint = %s\n", strerror(ret));
	}
	printf("**((int **)xx) = %i\n", *((int *)xx));
}
