#include "philo.h"

static void	even_num_phil(t_philo *philo)
{
	usleep(1000);
	pthread_mutex_lock(philo->left_fork);
	print_status(get_time(philo->start_life),
		philo->num, "\033[33m has taken a fork\033[0m\n", philo);
	pthread_mutex_lock(philo->right_fork);
	print_status(get_time(philo->start_life), philo->num, \
		"\033[33m has taken a fork\033[0m\n", philo);
}

int	take_forks(t_philo *philo)
{
	if (philo->num % 2)
	{
		if (philo->all->nbr_of_philosophers % 2)
			usleep(philo->all->time_to_eat);
		pthread_mutex_lock(philo->right_fork);
		print_status(get_time(philo->start_life), philo->num, \
				"\033[33m has taken a fork\033[0m\n", philo);
		if (philo->all->nbr_of_philosophers == 1)
		{
			mod_usleep(philo->all->time_to_die + 100, philo->start_life);
			return (0);
		}
		else
		{
			pthread_mutex_lock(philo->left_fork);
			print_status(get_time(philo->start_life), philo->num, \
				"\033[33m has taken a fork\033[0m\n", philo);
		}
	}
	else
		even_num_phil(philo);
	return (1);
}

void	eating(t_philo *philo)
{
	if (philo->all->check_death == 0)
	{
		if (take_forks(philo))
		{
			pthread_mutex_lock(&philo->all->status);
			philo->status = EAT;
			pthread_mutex_unlock(&philo->all->status);
			philo->eat_count++;
			philo->last_meal = get_time(philo->start_life);
			print_status(philo->last_meal, philo->num,
				"\033[32m is eating\033[0m\n", philo);
			mod_usleep(philo->all->time_to_eat, philo->start_life);
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
		}
	}
}

void	sleeping(t_philo *philo)
{
	if (philo->all->check_death == 0 && philo->status == EAT)
	{
		pthread_mutex_lock(&philo->all->status);
		philo->status = SLEEP;
		pthread_mutex_unlock(&philo->all->status);
		print_status(get_time(philo->start_life),
			philo->num, "\033[34m is sleeping\033[0m\n", philo);
		mod_usleep(philo->all->time_to_sleep, philo->start_life);
	}
}

void	thinking(t_philo *philo)
{
	if (philo->all->check_death == 0 && philo->status == SLEEP)
	{
		pthread_mutex_lock(&philo->all->status);
		philo->status = THINK;
		pthread_mutex_unlock(&philo->all->status);
		print_status(get_time(philo->start_life),
			philo->num, "\033[36m is thinking\033[0m\n", philo);
	}
}
