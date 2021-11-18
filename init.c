#include "philo.h"

int	init_struct(t_all *all, char **argv)
{
	all->nbr_of_philosophers = ft_atoi(argv[1]);
	all->nbr_of_forks = ft_atoi(argv[1]);
	all->time_to_die = ft_atoi(argv[2]);
	all->time_to_eat = ft_atoi(argv[3]);
	all->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		all->must_eat = ft_atoi(argv[5]);
	else
		all->must_eat = 0;
	all->check_death = 0;
	all->philo = NULL;
	all->forks = NULL;
	all->philo_thread = NULL;
	all->philo = (t_philo *) malloc(sizeof(t_philo) * all->nbr_of_philosophers);
	all->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
					all->nbr_of_forks);
	all->philo_thread = (pthread_t *)malloc(sizeof(pthread_t) * \
					all->nbr_of_philosophers);
	if (!all->philo_thread || !all->philo || !all->forks)
		return (free_struct("Error: memory allocation", all));
	return (0);
}

int	init_mutex(t_all *all)
{
	int		i;

	i = 0;
	if (pthread_mutex_init(&all->print_status, NULL) != 0)
		return (free_struct("Error: mutex init", all));
	if (pthread_mutex_init(&all->death_check, NULL) != 0)
		return (free_struct("Error: mutex init", all));
	if (pthread_mutex_init(&all->status, NULL) != 0)
		return (free_struct("Error: mutex init", all));
	while (i < all->nbr_of_forks)
	{
		if (pthread_mutex_init(&all->forks[i], NULL) != 0)
			return (free_struct("Error: mutex init", all));
		i++;
	}
	return (0);
}

void	init_philosophers(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->nbr_of_philosophers)
	{
		all->philo[i].num = i + 1;
		all->philo[i].all = all;
		all->philo[i].eat_count = 0;
		all->philo[i].status = THINK;
		all->philo[i].last_meal = 0;
		all->philo[i].stop = 0;
		all->philo[i].left_fork = &all->forks[i];
		if (i == 0)
			all->philo[i].right_fork = \
			&all->forks[all->nbr_of_philosophers - 1];
		else
			all->philo[i].right_fork = &all->forks[i - 1];
		i++;
	}	
}
