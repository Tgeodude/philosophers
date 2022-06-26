/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeodude <tgeodude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:44:28 by tgeodude          #+#    #+#             */
/*   Updated: 2022/06/26 21:34:55 by tgeodude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>

typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thread;

typedef struct s_philosophers
{
	t_mutex			*left_fork;
	t_mutex			*right_fork;
	t_mutex			*check;
	pthread_t		self;
	int				id;
	t_mutex			*ab_to_wr;
	int				times_need_to_eat;
	struct timeval	last;
	struct timeval	current_time;
	struct s_table	*table;
}	t_philosophers;

typedef struct s_table
{
	t_mutex			*forks;
	t_mutex			ab_to_wr;
	t_philosophers	*philosophers;
	int				num;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				number_of_time_to_eat;
	t_mutex			tmp;
	t_mutex			*checks;
	struct timeval	start;
	int				done;
}	t_table;

void	print_error(char *str);
int		ft_atoi(const char *str);
void	*routine(void *philosophers);
long	gettime(struct timeval start);
void	ft_usleep(int usec);
void	is_smd_dead(t_table *table);
long	timeval_comp(struct timeval fst, struct timeval snd);
void	ft_free(t_table *table);

#endif