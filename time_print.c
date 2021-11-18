#include "philo.h"

void	print_status(long time, int num, char *msg, t_philo *philo)
{
	pthread_mutex_lock(&philo->all->print_status);
	if (philo->all->check_death == 0)
		printf("%ld %d %s", time, num, msg);
	pthread_mutex_unlock(&philo->all->print_status);
}

long	get_time(long start)
{
	struct timeval	tv;
	long			current_time;

	gettimeofday(&tv, NULL);
	current_time = ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
	return (current_time - start);
}

void	mod_usleep(int time_to_sleep, long start)
{
	long	time;

	time = get_time(start);
	time = time + time_to_sleep;
	while (get_time(start) < time)
		usleep(500);
}
