#include "philo.h"

void	*phil_life(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (philo->all->check_death == 0)
	{
		if (philo->eat_count == philo->all->must_eat \
			&& philo->all->must_eat > 0)
			return (NULL);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	*check_death(void *phil)
{
	t_philo	*philo;
	long	time;

	philo = (t_philo *)phil;
	while (philo->all->check_death == 0)
	{
		usleep(100);
		pthread_mutex_lock(&philo->all->death_check);
		time = get_time(philo->start_life);
		if ((philo->all->time_to_die <= (time - philo->last_meal)))
		{
			if ((!philo->all->must_eat || philo->eat_count != philo->all->must_eat) \
				&& !philo->all->check_death)
				print_status(time, philo->num, "\033[31m died\033[0m\n", philo);
			philo->all->check_death = 1;
			pthread_mutex_unlock(&philo->all->death_check);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->all->death_check);
	}
	return (NULL);
}

void	begin_of_life(t_all *all)
{
	int				i;
	t_philo			*philo;
	pthread_t		death_control;
	unsigned long	start;

	i = 0;
	start = get_time(0);
	while (i < all->nbr_of_philosophers)
	{
		philo = &all->philo[i];
		philo->start_life = start;
		pthread_create(&all->philo_thread[i], NULL, &phil_life, philo);
		i++;
	}
	pthread_create(&death_control, NULL, &check_death, philo);
	pthread_join(death_control, NULL);
	i = 0;
	while (i < all->nbr_of_philosophers)
	{
		pthread_join(all->philo_thread[i], NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_all	all;

	if (argc > 6 || argc < 5 || check_args(argv, argc))
		return (check_error("Error: invalid arguments\n"));
	if (init_struct(&all, argv) || init_mutex(&all))
		return (1);
	init_philosophers(&all);
	begin_of_life(&all);
	if ((all.philo->eat_count == all.must_eat && all.must_eat > 0))
		printf("\033[35mEach philosopher ate %d times\033[0m\n", all.must_eat);
	free_all(&all);
	return (0);
}
