#ifndef PHILO_H
#define PHILO_H
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
typedef struct philo
{
	unsigned int	number_philos;
	unsigned int	t_eat;
	unsigned int	t_die;
	unsigned int	start_time;
	int				id;
	unsigned int	t_sleep;
	unsigned int	t_think;
	int				n_meals;
	int				meals_eaten;
	int				l_fork;
	int				r_fork;
	unsigned int	last_meal;
	pthread_mutex_t	*forks;
}	t_philo;
void			args_validity(char **argv);
int				error_message(char *msg);
unsigned int	ft_atoi(const char *str);
void			init_philo_stuff(t_philo *philo, char **argv, int argc);

#endif