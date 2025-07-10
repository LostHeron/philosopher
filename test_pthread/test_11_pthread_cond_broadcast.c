#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

typedef struct s_car_stat
{
	int				fuel;
	int				*p_getting_filled;
	int				*p_tank_fuel;
	pthread_mutex_t	*p_mutex_tank;
	pthread_cond_t	*p_cond_tank;
}	t_car_stat;

typedef struct s_tank_stat
{
	int				fuel;
	int				getting_filled;
	pthread_mutex_t	*p_mutex_tank;
	pthread_cond_t	*p_cond_tank;
}	t_tank_stat;

void	*car1_fill(void *arg)
{
	t_car_stat *car;

	car = arg;
	pthread_mutex_lock(car->p_mutex_tank);
	while (*car->p_tank_fuel < 40 && *car->p_getting_filled == 1)
	{
		printf("car1 : not enough fuel in the tank ... waiting\n");
		pthread_cond_wait(car->p_cond_tank, car->p_mutex_tank);
	}
	if (*car->p_tank_fuel >= 40)
	{
		car->fuel += 40;
		*car->p_tank_fuel -= 40;
		printf("car1 : filling fuel !\n");
	}
	else
		printf("car1 : could not get filled : not enough fuel\n");
	pthread_mutex_unlock(car->p_mutex_tank);
	return (NULL);
}

void	*car2_fill(void *arg)
{
	t_car_stat *car;

	car = arg;
	pthread_mutex_lock(car->p_mutex_tank);
	while (*car->p_tank_fuel < 40 && *car->p_getting_filled == 1)
	{
		printf("car2 : not enough fuel in the tank ... waiting\n");
		pthread_cond_wait(car->p_cond_tank, car->p_mutex_tank);
	}
	if (*car->p_tank_fuel >= 40)
	{
		car->fuel += 40;
		*car->p_tank_fuel -= 40;
		printf("car2 : filling fuel !\n");
	}
	else
		printf("car2 : could not get filled : not enough fuel\n");
	pthread_mutex_unlock(car->p_mutex_tank);
	return (NULL);
}

void	*car3_fill(void *arg)
{
	t_car_stat *car;

	car = arg;
	pthread_mutex_lock(car->p_mutex_tank);
	while (*car->p_tank_fuel < 40 && *car->p_getting_filled == 1)
	{
		printf("car3 : not enough fuel in the tank ... waiting\n");
		pthread_cond_wait(car->p_cond_tank, car->p_mutex_tank);
	}
	if (*car->p_tank_fuel >= 40)
	{
		car->fuel += 40;
		*car->p_tank_fuel -= 40;
		printf("car3 : filling fuel !\n");
	}
	else
		printf("car3 : could not get filled : not enough fuel\n");
	pthread_mutex_unlock(car->p_mutex_tank);
	return (NULL);
}

void	*tank_fill(void *arg)
{
	t_tank_stat *tank;
	int			ret;

	tank = arg;
	sleep(1);
	for (int i = 0; i < 5; i++)
	{
		pthread_mutex_lock(tank->p_mutex_tank);
		tank->fuel += 15;
		printf("filling tank ... %i\n", tank->fuel);
		ret = pthread_cond_broadcast(tank->p_cond_tank);
		if (ret != 0)
			printf("pthread_cond_broadcast : %s\n", strerror(ret));
		pthread_mutex_unlock(tank->p_mutex_tank);
		sleep(1);
	}
	pthread_mutex_lock(tank->p_mutex_tank);
	printf("tank no longer getting filled !\n");
	tank->getting_filled = 0;
	ret = pthread_cond_broadcast(tank->p_cond_tank);
	if (ret != 0)
		printf("pthread_cond_broadcast : %s\n", strerror(ret));
	pthread_mutex_unlock(tank->p_mutex_tank);
	return (NULL);
}

int	main(void)
{
	int				ret;
	pthread_t		t1;
	pthread_t		t2;
	pthread_t		t3;
	pthread_t		t4;
	t_car_stat		car1;
	t_car_stat		car2;
	t_car_stat		car3;
	t_tank_stat		tank;
	pthread_mutex_t	mutex_tank;
	pthread_cond_t	cond_tank;

	ret = pthread_mutex_init(&mutex_tank, NULL);
	if (ret != 0)
	{
		printf("pthread_mutex_init : %s\n", strerror(ret));
		return (1);
	}
	ret = pthread_cond_init(&cond_tank, NULL);
	if (ret != 0)
	{
		printf("pthread_cond_init : %s\n", strerror(ret));
		ret = pthread_mutex_destroy(&mutex_tank);
		if (ret != 0)
			printf("pthread_mutex_destroy : %s\n", strerror(ret));
		return (1);
	}
	tank.fuel = 0;
	tank.p_mutex_tank = &mutex_tank;
	tank.p_cond_tank = &cond_tank;
	tank.getting_filled = 1;
	car1.p_tank_fuel = &tank.fuel;
	car2.p_tank_fuel = &tank.fuel;
	car3.p_tank_fuel = &tank.fuel;
	car1.p_mutex_tank = &mutex_tank;
	car2.p_mutex_tank = &mutex_tank;
	car3.p_mutex_tank = &mutex_tank;
	car1.p_cond_tank = &cond_tank;
	car2.p_cond_tank = &cond_tank;
	car3.p_cond_tank = &cond_tank;
	car1.fuel = 0;
	car2.fuel = 0;
	car3.fuel = 0;
	car1.p_getting_filled = &tank.getting_filled;
	car2.p_getting_filled = &tank.getting_filled;
	car3.p_getting_filled = &tank.getting_filled;
	ret = pthread_create(&t1, NULL, &car1_fill, &car1);
	if (ret != 0)
	{
		printf("pthread_create %s\n", strerror(ret));
		// should free stuff but flemme
		return (1);
	}
	ret = pthread_create(&t2, NULL, &car2_fill, &car2);
	if (ret != 0)
	{
		printf("pthread_create %s\n", strerror(ret));
		// should free stuff but flemme
		return (1);
	}
	ret = pthread_create(&t3, NULL, &car3_fill, &car3);
	if (ret != 0)
	{
		printf("pthread_create %s\n", strerror(ret));
		// should free stuff but flemme
		return (1);
	}
	ret = pthread_create(&t4, NULL, &tank_fill, &tank);
	if (ret != 0)
	{
		printf("pthread_create %s\n", strerror(ret));
		// should free stuff but flemme
		return (1);
	}

	ret = pthread_join(t1, NULL);
	if (ret != 0)
	{
		printf("pthread_join %s\n", strerror(ret));
		// should free stuff but flemme
	}
	ret = pthread_join(t2, NULL);
	if (ret != 0)
	{
		printf("pthread_join %s\n", strerror(ret));
		// should free stuff but flemme
	}
	ret = pthread_join(t3, NULL);
	if (ret != 0)
	{
		printf("pthread_join %s\n", strerror(ret));
		// should free stuff but flemme
	}
	ret = pthread_join(t4, NULL);
	if (ret != 0)
	{
		printf("pthread_join %s\n", strerror(ret));
		// should free stuff but flemme
	}
	ret = pthread_mutex_destroy(&mutex_tank);
	if (ret != 0)
		printf("pthread_mutex_destroy : %s\n", strerror(ret));
	ret = pthread_cond_destroy(&cond_tank);
	if (ret != 0)
		printf("pthread_cond_destroy : %s\n", strerror(ret));
	return (0);
}
