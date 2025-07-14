#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	*routine(void *a)
{
	(void) a;
	printf("starting in the thread!\n");
	sleep(1);
	printf("in the thread!\n");
	sleep(1);
	printf("exiting the thread\n");
	return (NULL);
}

int	main(void)
{
	pthread_t	t1;
	int			ret;

	printf("starting thread !\n");
	ret = pthread_create(&t1, NULL, &routine, NULL);
	if (ret != 0)
		printf("pthread_create : %s\n", strerror(ret));
	printf("thread have been lunched !\n");
	pthread_exit(0);
	ret = pthread_join(t1, NULL);
	if (ret != 0)
		printf("pthread_join : %s\n", strerror(ret));
	printf("thread have been joint \n");
	return (0);
}
