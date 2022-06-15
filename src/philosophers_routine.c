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
	pthread_mutex_unlock(philosophers->ab_to_wr);
	ft_usleep(philosophers->table->time_eat);
    pthread_mutex_unlock(philosophers->left_fork);
    pthread_mutex_unlock(philosophers->right_fork);
}

void	contemplate(t_philosophers *philosophers)
{
	pthread_mutex_lock(philosophers->ab_to_wr);
	printf("%ld %d is sleeping\n", gettime(philosophers->table->start), philosophers->id);
	pthread_mutex_unlock(philosophers->ab_to_wr);
	ft_usleep(philosophers->table->time_sleep);
	pthread_mutex_lock(philosophers->ab_to_wr);
	printf("%ld %d is contemplate\n", gettime(philosophers->table->start), philosophers->id);
	pthread_mutex_unlock(philosophers->ab_to_wr);
}

void    *routine(void *philosopher)
{
    t_philosophers *philosophers;

    philosophers = (t_philosophers *)philosopher;
    while (philosophers->table->number_of_time_to_eat)
    {
        eating(philosophers);
        contemplate(philosophers);
        philosophers->table->number_of_time_to_eat--;
    }
    return (0);
}