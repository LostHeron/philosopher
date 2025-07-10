#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#define NB_STOVES 2
#define NB_CHIEFS 10
#define BASE_FUEL 200

// OK try to do same program but instead of 
// stove[NB_STOVE]
// let delcase a single stove struce
// and inside that structure delcare two array of 4
// one of pthread_mutex_t [4]
// and one of int [4] 
// and see if that resolves the problems of data raise 

typedef struct s_stove
{
	int				*p_fuels;
	pthread_mutex_t	mutex;
}	t_stove;

static int	init_mutexes(t_stove *stoves);
static int	clear_mutexes(t_stove *stoves, int nb);
static int	start_threads(pthread_t	*ts, t_stove *stoves);
static int	join_threads(pthread_t *ts, int nb);
void	*routine(void *arg);

int	main(void)
{
	pthread_t		ts[NB_CHIEFS];
	/*
	pthread_mutex_t	mutexes[NB_STOVES];
	int				fuels[NB_STOVES];
	*/
	t_stove			stoves[NB_STOVES];
	int				ret;
	int				fuels[2];

	fuels[0] = BASE_FUEL;
	fuels[1] = BASE_FUEL;
	stoves[0].p_fuels = fuels + 0;
	stoves[1].p_fuels = fuels + 1;
	ret = init_mutexes(stoves);
	if (ret != 0)
		return (ret);
	ret = start_threads(ts, stoves);
	if (ret != 0)
	{
		clear_mutexes(stoves, NB_STOVES);
		return (ret);
	}
	int	final_ret = 0;
	ret = join_threads(ts, NB_CHIEFS);
	if (ret != 0)
		final_ret = 1;
	ret = clear_mutexes(stoves, NB_STOVES);
	if (ret != 0)
		final_ret = 1;
	for (int i = 0; i < NB_STOVES; i++)
	{
		printf("stove[%i].fuels = %i\n", i, *stoves[i].p_fuels);
	}
	return	(final_ret);
}

static int	init_mutexes(t_stove *stoves)
{
	int	ret;

	for (int i = 0; i < NB_STOVES; i++)
	{
		ret = pthread_mutex_init(&stoves[i].mutex, NULL);
		if (ret != 0)
		{
			clear_mutexes(stoves, i);
			printf("pthread_mutex_init : %s\n", strerror(ret));
			return (1);
		}
	}
	return (0);
}

static int	clear_mutexes(t_stove *stoves, int nb)
{
	int	ret;
	int	final_ret;

	for (int j = 0; j < nb; j++)
	{
		ret = pthread_mutex_destroy(&stoves[j].mutex);
		if (ret != 0)
		{
			printf("pthread_mutex_destroy : %s\n", strerror(ret));
			final_ret = 1;
		}
	}
	return (final_ret);
}

static int	start_threads(pthread_t	*ts, t_stove *stoves)
{
	int	ret;
	int	final_ret;

	final_ret = 0;
	for (int i = 0; i < NB_CHIEFS; i++)
	{
		ret = pthread_create(ts + i, NULL, &routine, stoves);
		if (ret != 0)
		{
			printf("pthread_create : %s\n", strerror(ret));
			join_threads(ts, i);
			final_ret = 1;
		}
	}
	return (final_ret);
}

void	*routine(void *arg)
{
	int		keep_working;
	int		ret;
	t_stove *stoves;
	int		locked_all_mutex;
	int		could_work;	

	printf("starting routine !\n");
	stoves = arg;
	keep_working = 1;
	while (keep_working == 1)
	{
		locked_all_mutex = 1;
		could_work = 0;
		usleep(500000);
		for (int i = 0; i < NB_STOVES; i++)
		{
			ret = pthread_mutex_trylock(&(stoves[i].mutex));
			if (ret == 0)
			{
				if (*stoves[i].p_fuels - 20 >= 0)
				{
					printf("before : stove[%i].fuels = %i\n", i, *stoves[i].p_fuels);
					*stoves[i].p_fuels -= 20;
					printf("after : stove[%i].fuels = %i\n", i, *stoves[i].p_fuels);
					could_work = 1;
					printf("could work !\n");
				}
				pthread_mutex_unlock(&(stoves[i].mutex));
			}
			else
			{
				locked_all_mutex = 0;
			}
		}
		if (locked_all_mutex == 1 && could_work == 0)
			keep_working = 0;
	}
	printf("going_home !\n");
	return (NULL);
}

static int	join_threads(pthread_t *ts, int nb)
{
	int	ret;
	int	final_ret;

	final_ret = 0;
	for (int i = 0; i < nb; i++)
	{
		ret = pthread_join(ts[i], NULL);
		if (ret != 0)
		{
			printf("pthread_joint : %s\n", strerror(ret));
			final_ret = 1;
		}
	}
	return (final_ret);
}
