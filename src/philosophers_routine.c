#include "philosophers.h"

void    eating(t_philosophers *philosophers)
{
    pthread_mutex_lock(philosophers->left_fork);
    pthread_mutex_lock(philosophers->ab_to_wr);
    printf("%ld %d philosopers taken left fork\n", gettime(philosophers->table->start), philosophers->id);
    pthread_mutex_unlock(philosophers->ab_to_wr);
    pthread_mutex_lock(philosophers->right_fork);
    pthread_mutex_lock(philosophers->ab_to_wr);
    printf("%ld %d philosopers taken  right fork\n%ld %d is eating\n", gettime(philosophers->table->start), philosophers->id, gettime(philosophers->table->start), philosophers->id);
	pthread_mutex_lock(philosophers->check);
	gettimeofday(&philosophers->last, NULL);
	pthread_mutex_unlock(philosophers->check);
	pthread_mutex_unlock(philosophers->ab_to_wr);
	ft_usleep(philosophers->table->time_eat);
	pthread_mutex_lock(philosophers->ab_to_wr);
    pthread_mutex_unlock(philosophers->right_fork);
    pthread_mutex_unlock(philosophers->left_fork);
}

void	contemplate(t_philosophers *philosophers)
{
	printf("%ld %d is sleeping\n", gettime(philosophers->table->start), philosophers->id);
	pthread_mutex_unlock(philosophers->ab_to_wr);
	ft_usleep(philosophers->table->time_sleep);
	gettimeofday(&philosophers->current_time, NULL);
	pthread_mutex_lock(philosophers->ab_to_wr);
	printf("%ld %d is thinking\n", gettime(philosophers->table->start), philosophers->id);
	pthread_mutex_unlock(philosophers->ab_to_wr);
}

void is_smd_dead(t_table *table)
{
    struct timeval	tmp;
    int				i;

	i = 0;
	while (1)
	{
		gettimeofday(&tmp, NULL);
		pthread_mutex_lock(table->philosophers[i].check);
		if (timeval_comp(table->philosophers[i].last, tmp) / 1000 > table->time_die && table->philosophers[i].times_need_to_eat)
		{
			pthread_mutex_lock(&(table->ab_to_wr));
			printf("%ld %d died\n", gettime(table->start), i + 1);
			break ;
		}
		if (table->done == table->num)
			break ;
		pthread_mutex_unlock(table->philosophers[i].check);
		i = (i + 1) % table->num;
	}
}

void    *routine(void *philosopher)
{
    t_philosophers *philosophers;

    philosophers = (t_philosophers *)philosopher;
    while (philosophers->table->number_of_time_to_eat)
    {
        eating(philosophers);
        contemplate(philosophers);
        --philosophers->table->number_of_time_to_eat;
    }
	++philosophers->table->done;
    return (0);
}