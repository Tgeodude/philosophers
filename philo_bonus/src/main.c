/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeodude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 23:48:37 by tgeodude          #+#    #+#             */
/*   Updated: 2022/06/26 23:48:39 by tgeodude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	philo_life(t_ph *philo, t_all *g_all)
{
	sem_wait(g_all->fork);
	philo_print("has taken a fork", philo->number, 1, g_all);
	sem_wait(g_all->fork);
	philo_print("has taken a fork", philo->number, 1, g_all);
	philo_print("is eating", philo->number, 1, g_all);
	philo->last = get_time();
	usleep(g_all->t_eat * 1000);
	philo->n_eat++;
	sem_post(g_all->fork);
	sem_post(g_all->fork);
	philo_print("is sleeping", philo->number, 1, g_all);
	usleep(g_all->t_sleep * 1000);
	philo_print("is thinking", philo->number, 1, g_all);
	return (1);
}

void	*philo_checker(void	*arg)
{
	t_ph	*philo;

	philo = (t_ph *)arg;
	usleep(5);
	while (1 && !philo->died)
	{
		if ((unsigned long)philo->t_die < (get_time() - philo->last))
		{
			sem_wait(philo->g_all->check);
			philo_print("\033[0;31m\033[1mdied \033[0m", \
			philo->number, 0, philo->g_all);
			philo->died = 1;
			break ;
		}
		if (philo->n_eat >= philo->g_all->c_eat && philo->g_all->c_eat != -1)
		{
			philo->died = 1;
			sem_wait(philo->g_all->check);
			break ;
		}
	}
	return (arg);
}

void	philo_routine(t_ph *philo, t_all *g_all)
{
	if (philo->number % 2 == 0)
		usleep(100);
	philo->last = get_time();
	if (pthread_create(&philo->checker, NULL, philo_checker, philo))
		return ;
	while (!(philo->died))
		philo_life(philo, g_all);
	pthread_detach(philo->checker);
	if (philo->died)
		exit(1);
	exit(0);
}

int	philo_start(int i, t_all *g_all)
{
	int	status;

	while (++i < g_all->num)
	{
		g_all->philo[i].number = i + 1;
		g_all->philo[i].n_eat = 0;
		g_all->philo[i].t_die = g_all->t_die;
		g_all->philo[i].g_all = g_all;
		g_all->philo[i].died = 0;
	}
	g_all->start = get_time();
	i = -1;
	while (++i < g_all->num)
	{
		g_all->philo[i].pid = fork();
		if (g_all->philo[i].pid == 0)
			philo_routine(&(g_all->philo[i]), g_all);
	}
	while (1)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status))
			break ;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_all	g_all;
	int		i;

	if (argc < 5 || argc > 6 || check_init(argc, argv, &g_all))
		return (write(2, "Wrong arguments\n", 16) - 15);
	if (g_all.fork == SEM_FAILED)
		return (write(2, "Error with semaphor\n", 20) - 19);
	if (philo_start(-1, &g_all))
		return (1);
	sem_unlink("print");
	sem_unlink("fork");
	sem_unlink("check");
	i = -1;
	while (++i < g_all.num && g_all.philo[i].pid)
		kill(g_all.philo[i].pid, 9);
	free(g_all.philo);
	return (0);
}
