#include "philosophers.h"

void    eating(t_philosophers *philosophers)
{
    pthread_mutex_lock(philosophers->left_fork);
    pthread_mutex_lock(philosophers->ab_to_wr);
    printf("philosopers taken left fork\n");
    pthread_mutex_unlock(philosophers->ab_to_wr);
    pthread_mutex_lock(philosophers->right_fork);
    pthread_mutex_lock(philosophers->ab_to_wr);
    printf("philosopers taken write fork\n");
    pthread_mutex_unlock(philosophers->ab_to_wr);
    pthread_mutex_unlock(philosophers->left_fork);
    pthread_mutex_unlock(philosophers->right_fork);
}

void    *routine(void *philosopher)
{
    t_philosophers *philosophers;

    philosophers = (t_philosophers *)philosopher;
    while (philosophers->times_need_to_eat)
    {
        eating(philosophers);
        //contemplate(philosophers);
        philosophers->times_need_to_eat--;
    }
    return (0);
}