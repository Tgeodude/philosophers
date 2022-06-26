/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeodude <tgeodude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 21:44:26 by tgeodude          #+#    #+#             */
/*   Updated: 2022/06/26 21:44:33 by tgeodude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ft_free(t_table *table)
{
	free(table->checks);
	free(table->forks);
	free(table->philosophers);
}
