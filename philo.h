#ifndef PHILO_H
#define PHILO_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
typedef struct philo
{
	int				number_philos;
	int				t_eat;
	int				died;
	int				s_time;
	int				t_die;
	int				start_time;
	int				id;
	int				t_sleep;
	int				t_think;
	int				n_meals;
	int				meals_eaten;
	int				last_meal;
	pthread_mutex_t	*printing;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t *meal_mtx;
	pthread_mutex_t	*forks;
}	t_philo;

int			args_validity(char **argv);
int	limits_of_dying(t_philo *philo);
void    *monitor_philos(void *arg);
int				error_message(char *msg);
long	get_time(void);
unsigned int	ft_atoi(const char *str);
void			init_philo(t_philo *philo, char **argv, int argc);
void	init_mutex_for_forks(t_philo *philo, char *argv1);
void	safe_print(t_philo *philo, char *msg);
int	ft_strlen(char *str);
int	check_dies(t_philo *philo);

#endif