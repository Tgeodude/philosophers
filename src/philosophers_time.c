#include "philosophers.h"

long	gettime(struct timeval start)
{
	struct timeval	last;
	long			res;

	gettimeofday(&last, NULL);
	res = 1000 * (size_t)last.tv_sec + (size_t)last.tv_usec / 1000 ;
	res -= 1000 * (size_t)start.tv_sec + (size_t)start.tv_usec / 1000;
	return (res);
}

long	ft_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (1000 * (size_t)tv.tv_sec + (size_t)tv.tv_usec / 1000);
}

void	ft_usleep(int usec)
{
	long	time;

	time = ft_time();
	usleep(usec * 920);
	while (ft_time() < time + usec)
		usleep(usec * 3);
}