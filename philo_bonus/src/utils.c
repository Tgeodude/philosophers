#include "philosophers.h"

void	check_atoi(const char *str, int h, int i)
{
	if ((str[0]) == '9' && h == 214748364)
	{
		if (i == -1)
		{
			write(2, "Error\n", 6);
			exit(0);
		}
	}
	if (h > 214748364)
	{
		write(2, "Error\n", 6);
		exit(0);
	}
	if (i != -1 && h == 214748364 && ((*str) - '0') > 7)
	{
		write(2, "Error\n", 6);
		exit(0);
	}
}

void	chech_atoi_one(const char *str, int h, int i)
{
	if ((str[0]) == '9' && h == 214748364)
	{
		if (i == -1)
		{
			write(2, "Error\n", 6);
			exit(0);
		}
	}
}

int	ft_atoi(const char *str)
{
	int	i;
	int	h;

	h = 0;
	i = 1;
	while ((*str) == ' ' || ((*str) >= '\t' && (*str) <= '\r'))
		++str;
	if ((*str) == '-' || (*str) == '+')
	{
		if ((*str == '-'))
			i = -1;
		++str;
	}
	while ((*str) >= '0' && (*str) <= '9')
	{
		chech_atoi_one(str, h, i);
		check_atoi(str, h, i);
		h = (h * 10) + ((*str) - '0');
		++str;
	}
	return (h * i);
}

long get_time (void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	philo_print(char *str, int number, int status, t_all *g_all)
{
	if (status == 2)
		exit(1);
	sem_wait(g_all->write);
	sem_wait(g_all->check);
	printf("%lu %d %s\n", (get_time() - g_all->start), number, str);
	if (status == 0)
		exit(1);
	sem_post(g_all->write);
	sem_post(g_all->check);
	return (0);
}