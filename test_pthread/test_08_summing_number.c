#include <pthread.h>
#include <stdio.h>
#include <string.h>

#define NB_NUM 9
#define NB_THREAD 2

void	*my_sum(void *num)
{
	int	sum;

	sum = 0;
	printf("i = %i\n", NB_NUM / NB_THREAD);
	printf("num[0] = %i\n", ((int *)num)[0]);
	for (int i = 0; i < NB_NUM / NB_THREAD; i++)
	{
		printf("on ajoute : %i\n", ((int *)num)[i]);
		sum += ((int *)num)[i];
	}
	((int *)num)[0] = sum;
	return (num);
}

void	*last_sum(void *num)
{
	int	sum;

	printf("call to last_sum\n");
	sum = 0;
	for (int i = 0; i < NB_NUM % NB_THREAD; i++)
	{
		sum += ((int *)num)[i];
	}
	((int *)num)[0] = sum;
	return (num);
}

int	main(void)
{
	int			final_ret;
	int			ret;
	int			*x;
	int			sum;
	int			num[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	pthread_t	ts[NB_THREAD + 1];

	for (int i = 0; i < NB_THREAD; i++)
	{
		ret = pthread_create(ts + i, NULL, &my_sum, num + i * (NB_NUM / NB_THREAD));
		if (ret != 0)
		{
			printf("pthread_create : %s\n", strerror(ret));
			for (int j = 0; j < i; j++)
			{
				ret = pthread_join(ts[j], NULL);
				{
					if (ret != 0)
					{
						printf("pthread_join : %s\n", strerror(ret));
					}
				}
			}
			return (1);
		}
	}
	if (NB_NUM % NB_THREAD != 0)
	{
		ret = pthread_create(ts + NB_THREAD, NULL, &last_sum, num + NB_NUM - (NB_NUM % NB_THREAD));
		if (ret != 0)
		{
			printf("pthread_create : %s\n", strerror(ret));
			for (int j = 0; j < NB_THREAD; j++)
			{
				ret = pthread_join(ts[j], NULL);
				{
					if (ret != 0)
					{
						printf("pthread_join : %s\n", strerror(ret));
					}
				}
			}
			return (1);
		}
	}
	sum = 0;
	final_ret = 0;
	for (int i = 0; i < NB_THREAD; i++)
	{
		ret = pthread_join(ts[i], (void *) &x);
		if (ret != 0)
		{
			printf("pthread_joint : %s\n", strerror(ret));
			final_ret = 1;
		}
		sum += *x;
	}
	if (NB_NUM % NB_THREAD != 0)
	{
		ret = pthread_join(ts[NB_THREAD], (void *) &x);
		if (ret != 0)
		{
			printf("pthread_join : %s\n", strerror(ret));
			final_ret = 1;
		}
		sum += *x;
	}
	if (final_ret == 0)
		printf("sum = %i\n", sum);
	return (final_ret);
}
