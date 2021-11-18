#ifndef PHILO_H
# define PHILO_H

# include "libft/libft.h"
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <errno.h>
# include <limits.h>

# define EAT 0
# define SLEEP 1
# define THINK 2

typedef struct s_philo
{
	int				num;
	int				status;
	int				eat_count;
	long			start_life;
	long			last_meal;
	int				stop;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_all	*all;
}				t_philo;

typedef struct s_all
{
	int				nbr_of_philosophers;
	int				nbr_of_forks;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				check_death;
	t_philo			*philo;
	pthread_t		*philo_thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t	status;
	pthread_mutex_t	print_status;
	pthread_mutex_t	death_check;
}				t_all;

int		init_struct(t_all *all, char **argv);
int		init_mutex(t_all *all);
void	init_philosophers(t_all *all);
int		free_struct(char *str, t_all *all);
void	free_all(t_all *all);
int		check_error(char *str);
void	begin_of_life(t_all *all);
int		check_args(char **argv, int argc);
long	get_time(long start);
void	end_of_life(t_all *all);
void	*phil_life(void *data);
void	print_status(long time, int num, char *msg, t_philo *philo);
void	*check_death(void *phil);
int		take_forks(t_philo *philo);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);
void	mod_usleep(int length, long start);
long	get_time(long start);

#endif
