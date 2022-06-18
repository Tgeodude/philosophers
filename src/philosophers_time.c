#include "philosophers.h"

long	gettime(struct timeval start)
{
	struct timeval	last;

	gettimeofday(&last, NULL);
	return ((1000 * (size_t)last.tv_sec + (size_t)last.tv_usec / 1000) - (1000 * (size_t)start.tv_sec + (size_t)start.tv_usec / 1000) );
}

long	ft_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (1000 * (size_t)tv.tv_sec + (size_t)tv.tv_usec / 1000);
}

long	timeval_comp(struct timeval fst, struct timeval snd)
{
	return (snd.tv_usec - fst.tv_usec + (snd.tv_sec - fst.tv_sec) * 1000000);
}

void	ft_usleep(int usec)
{
	long	time;

	time = ft_time();
	usleep(usec * 900);
	while (ft_time() < time + usec)
		usleep(usec * 10);
}