#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define NB_PRIMES 10

void	*print_primes(void *prime_i)
{
	sleep(1);
	printf("prime : %i\n", *((int *)prime_i));
	return (NULL);
}

int	main(void)
{
	int			final_ret;
	int			ret;
	int			first_primes[NB_PRIMES] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
	pthread_t	ts[NB_PRIMES];

	for (int i = 0; i < NB_PRIMES; i++)
	{
		ret = pthread_create(ts + i, NULL, &print_primes, first_primes + i);
		if (ret != 0)
		{
			printf("pthread_create : %s\n", strerror(ret));
			for (int j = 0; j < i; j++)
			{
				ret = pthread_join(ts[j], NULL);
				if (ret != 0)
				{
					printf("pthread_join : %s\n", strerror(ret));
				}
			}
			return (1);
		}
	}
	final_ret = 0;
	for (int i = 0; i < NB_PRIMES; i++)
	{
		ret = pthread_join(ts[i], NULL);
		if (ret != 0)
		{
			printf("pthread_join : %s\n", strerror(ret));
			final_ret = 1;
		}
	}
	return (final_ret);
}
