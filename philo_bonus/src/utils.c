/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeodude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 23:59:39 by tgeodude          #+#    #+#             */
/*   Updated: 2022/06/26 23:59:40 by tgeodude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	ft_atoi(const char *str)
{
	unsigned long long	sum;

	sum = 0;
	if (*str == '+')
		str++;
	if (*str == '0')
		return (0);
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (0);
		sum = sum * 10 + *str - '0';
		str++;
	}
	if (sum > 2147483647)
		return (-1);
	if (sum > 2147483648)
		return (0);
	return ((int)sum);
}

int	check_init(int argc, char **argv, t_all *g_all)
{	
	g_all->num = ft_atoi(argv[1]);
	g_all->t_die = ft_atoi(argv[2]);
	g_all->t_eat = ft_atoi(argv[3]);
	g_all->t_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		g_all->c_eat = -1;
	else
		g_all->c_eat = ft_atoi(argv[5]);
	sem_unlink("fork");
	sem_unlink("print");
	sem_unlink("check");
	g_all->philo = (t_ph *)malloc(sizeof(t_ph) * g_all->num);
	if (g_all->num < 2 || g_all->t_die < 0 \
			|| g_all->t_eat < 0 || g_all->t_sleep < 0 \
			|| (argc == 6 && g_all->c_eat < 0) \
			|| g_all->num > 200)
	{
		free(g_all->philo);
		return (1);
	}
	g_all->fork = sem_open("fork", O_CREAT | O_EXCL, S_IRWXU, g_all->num);
	g_all->write = sem_open("write", O_CREAT | O_EXCL, S_IRWXU, 1);
	g_all->check = sem_open("check", O_CREAT | O_EXCL, S_IRWXU, 1);
	return (0);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	philo_print(char *str, int number, int status, t_all *g_all)
{
	sem_wait(g_all->write);
	printf("%lu %d %s\n", (get_time() - g_all->start), number, str);
	if (status == 0)
		exit(1);
	sem_post(g_all->write);
	return (0);
}
