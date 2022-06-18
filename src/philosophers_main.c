#include "philosophers.h"

void	parse(int argc, char **argv, t_table *table)
{
	table->num = ft_atoi(argv[1]);
	table->time_die = ft_atoi(argv[2]);
	table->time_eat = ft_atoi(argv[3]);
	table->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->number_of_time_to_eat = ft_atoi(argv[5]);
	else
		table->number_of_time_to_eat = -1;
}

int	mutex_init(t_table *table)
{
	int	i;

	table->forks = (t_mutex *)malloc(sizeof(t_mutex) * table->num);
	if (!table->forks)
		return (0);
	table->checks = (t_mutex *)malloc(sizeof(t_mutex)* table->num);
	if (!table->checks)
		return (0);
	i = -1;
	while (++i < table->num)
		if (pthread_mutex_init(table->forks + i, NULL) || pthread_mutex_init(table->checks + i, NULL))
			return (0);
	return (1);
}

int	create_philo(t_table *table, int i)
{
	table->philosophers[i].table = table;
	table->philosophers[i].ab_to_wr = &table->ab_to_wr;
	table->philosophers[i].left_fork = table->forks + i;
	table->philosophers[i].times_need_to_eat = table->number_of_time_to_eat;
	table->philosophers[i].check = table->checks + i;
	table->philosophers[i].id = i + 1;
	table->philosophers[i].last = table->start;
	if (i != table->num - 1)
		table->philosophers[i].right_fork = table->forks + i + 1;
	else
		table->philosophers[i].right_fork = table->forks;
	if (pthread_create(&table->philosophers[i].self, NULL, routine, (void *)((table->philosophers) + i)))
		return (0);
	return (1);
}

int	philo_init(t_table *table)
{
	int	i;

	gettimeofday(&table->start, NULL);
	table->philosophers = (t_philosophers *) malloc(sizeof(t_philosophers) * table->num);
	i = 0;
	while (i < table->num)
	{
		create_philo(table, i);
		i += 2;
	}
	usleep(100);
	i = 1;
	while (i < table->num)
	{
		create_philo(table, i);
		i += 2;
	}
	usleep(100);
	return (1);
	
}

int	main(int argc, char **argv)
{
	t_table table;

	memset(&table, 0, sizeof(table));
	if (argc == 5 || argc == 6)
		parse(argc, argv, &table);
	else
		print_error("Incorrect input");
	pthread_mutex_init(&(table.ab_to_wr), NULL);
	if (!(mutex_init(&table)))
		print_error("Error in mutex");
	if (!(philo_init(&table)))
		print_error("Error in philo create");
	is_smd_dead(&table);
	ft_free(&table);
}