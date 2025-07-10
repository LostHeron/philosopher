#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

pthread_mutex_t	mutex_tank;
int				tank_fuel = 0;
int				car_fuel = 0;

void	*tank_filling(void *a)
{
	int	ret;

	(void) a;
	for (int i = 0; i < 5; i++)
	{
		ret = pthread_mutex_lock(&mutex_tank);
		if (ret != 0)
			printf("pthread_mutex_lock : %s\n", strerror(ret));
		else
		{
			tank_fuel += 15;
			printf("fillin tank ... %i\n", tank_fuel);
			ret = pthread_mutex_unlock(&mutex_tank);
			if (ret != 0)
				printf("pthread_mutex_unlock : %s\n", strerror(ret));
		}
		sleep(1);
	}
	return (NULL);
}

void	*car_filling(void *a)
{
	int	ret;
	int	local_tank_fuel;

	pthread_mutex_lock(&mutex_tank);
	local_tank_fuel = tank_fuel;
	pthread_mutex_unlock(&mutex_tank);
	while (local_tank_fuel < 40)
	{
		printf("no enough fuel ... waiting \n");
		sleep(1);
		// to avoid doing these stuff here, we can use
		// the pthread api with the pthread_cond_wait ! 
		pthread_mutex_lock(&mutex_tank);
		local_tank_fuel = tank_fuel;
		pthread_mutex_unlock(&mutex_tank);
	}
	ret = pthread_mutex_lock(&mutex_tank);
	if (ret != 0)
		printf("pthread_mutex_lock : %s\n", strerror(ret));
	else
	{
		tank_fuel -= 40;
		car_fuel += 40;
		printf("filling car : car fuel : %i, tank fuel : %i\n", car_fuel, tank_fuel);
		ret = pthread_mutex_unlock(&mutex_tank);
		if (ret != 0)
		{
			printf("pthread_mutex_unlock : %s\n", strerror(ret));
		}
	}
	(void) a;
	return (NULL);
}

int	main(void)
{
	int			final_ret;
	int			ret;
	pthread_t	t_tank;
	pthread_t	t_car;

	ret = pthread_mutex_init(&mutex_tank, NULL);
	if (ret != 0)
	{
		printf("pthread_mutex_init : %s\n", strerror(ret));
		return (1);
	}
	ret = pthread_create(&t_tank, NULL, &tank_filling, NULL);
	if (ret != 0)
	{
		printf("pthread_create : %s\n", strerror(ret));
		ret = pthread_mutex_init(&mutex_tank, NULL);
		if (ret != 0)
			printf("pthread_mutex_init : %s\n", strerror(ret));
		return (1);
	}
	ret = pthread_create(&t_car, NULL, &car_filling, NULL);
	if (ret != 0)
	{
		printf("pthread_create : %s\n", strerror(ret));
		ret = pthread_join(t_car, NULL);
		if (ret != 0)
			printf("pthread_join : %s\n", strerror(ret));
		ret = pthread_mutex_init(&mutex_tank, NULL);
		if (ret != 0)
			printf("pthread_mutex_init : %s\n", strerror(ret));
		return (1);
	}
	final_ret = 0;
	ret = pthread_join(t_car, NULL);
	if (ret != 0)
	{
		printf("pthread_join : %s\n", strerror(ret));
		final_ret = 1;
	}
	ret = pthread_join(t_tank, NULL);
	if (ret != 0)
	{
		printf("pthread_join : %s\n", strerror(ret));
		final_ret = 1;
	}
	ret = pthread_mutex_init(&mutex_tank, NULL);
	if (ret != 0)
	{
		printf("pthread_mutex_init : %s\n", strerror(ret));
		final_ret = 1;
	}
	return (final_ret);
}
