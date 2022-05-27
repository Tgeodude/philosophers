#include "philosophers.h"

void	init_table_and_philosophers(int argc, char **argv, t_table *table)
{
	table->num = ft_atoi(argv[1]);
	table->time_die = ft_atoi(argv[2]);
	table->time_eat = ft_atoi(argv[3]);
	table->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->number_of_time_to_eat = ft_atoi(argv[5]);
	else
		table->number_of_time_to_eat = -1;
	table->forks = (t_mutex *)malloc(sizeof(t_mutex) * table->num);
	table->philosophers = malloc(sizeof(t_philosophers) * table->num);
}

int	main(int argc, char **argv)
{
	t_table table;
	pthread_mutex_init(&(table.tmp), NULL);
	if (argc == 5 || argc == 6)
		init_table_and_philosophers(argc, argv, &table);
	else
		print_error("Incorrect input");
	
}