/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeodude <tgeodude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:44:28 by tgeodude          #+#    #+#             */
/*   Updated: 2022/05/26 18:11:19 by tgeodude         ###   ########.fr       */
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

typedef struct s_philosophers				// структура данных философов
{
    t_mutex left_fork;						// левая вилка каждого философа - mutex
    t_mutex right_fork;						// правая вилка каждого философа - mutex
	struct t_table	*table;
} t_philosophers;

typedef struct s_table						// структура данных стола
{
	t_mutex			forks;					// все вилки на столе - mutex 
    t_philosophers	philosophers;			// ссылка на структуру философов 
	int				num;					// колл-во вилок на столе
	int				time_die;				// через сколько философ умреть если не поест	
	int				time_eat;				// сколько философу нужно есть по времени
	int				time_sleep;				// сколько философу нужно спать по времени
	int				number_of_time_to_eat;	// сколько раз должен поесть философ чтобы программа завершилась
} t_table;

void    print_error(char *str);				// вывод ошибок
int		ft_atoi(const char *str);			// функция дле преобразования чисел из char в int

#endif