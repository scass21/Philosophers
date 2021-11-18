#include "philo.h"

int	free_struct(char *str, t_all *all)
{
	if (all->philo)
		free(all->philo);
	if (all->forks)
		free(all->forks);
	if (all->philo_thread)
		free(all->philo_thread);
	return (check_error(str));
}

void	destroy_mutex(t_all *all, int i)
{
	if (pthread_mutex_destroy(&all->forks[i]) == EBUSY)
	{
		pthread_mutex_unlock(&all->forks[i]);
		pthread_mutex_destroy(&all->forks[i]);
	}
	if (pthread_mutex_destroy(all->philo[i].left_fork) == EBUSY)
	{
		pthread_mutex_unlock(all->philo[i].left_fork);
		pthread_mutex_destroy(all->philo[i].left_fork);
	}
	if (pthread_mutex_destroy(all->philo[i].right_fork) == EBUSY)
	{
		pthread_mutex_unlock(all->philo[i].right_fork);
		pthread_mutex_destroy(all->philo[i].right_fork);
	}
}

void	free_all(t_all *all)
{
	int	i;

	pthread_mutex_unlock(&all->print_status);
	pthread_mutex_destroy(&all->print_status);
	pthread_mutex_unlock(&all->death_check);
	pthread_mutex_destroy(&all->death_check);
	pthread_mutex_unlock(&all->status);
	pthread_mutex_destroy(&all->status);
	i = 0;
	while (i < all->nbr_of_forks)
	{
		destroy_mutex(all, i);
		i++;
	}
	free_struct(NULL, all);
}

int	check_error(char *str)
{
	ft_putstr_fd(str, 2);
	return (1);
}

int	check_args(char **argv, int argc)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) <= 0)
			return (1);
		i++;
	}
	return (0);
}
