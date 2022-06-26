/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeodude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 23:38:54 by tgeodude          #+#    #+#             */
/*   Updated: 2022/06/26 23:38:58 by tgeodude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <semaphore.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h> 
# include <sys/wait.h>
# include <stdlib.h>
# include <signal.h>

typedef struct s_ph
{
	pid_t			pid;
	pthread_t		checker;
	unsigned long	last;
	int				number;
	int				n_eat;
	int				t_die;
	struct s_all	*g_all;
	int				died;
}	t_ph;

typedef struct s_all
{
	sem_t			*fork;
	sem_t			*write;
	sem_t			*check;
	unsigned long	start;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				c_eat;
	int				done;
	int				id;
	int				num;
	int				count_eat;
	t_ph			*philo;
}	t_all;

int		ft_atoi(const char *str);
long	get_time(void);
int		philo_print(char *str, int number, int status, t_all *g_all);
int		check_init(int argc, char **argv, t_all *g_all);

#endif
