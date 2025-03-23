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
	int				s_time;
	int				t_die;
	int				start_time;
	int				id;
	int				t_sleep;
	int				t_think;
	int				n_meals;
	int				meals_eaten;
	long			last_meal;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*print_mtx;
	int				dead_flag;
	pthread_mutex_t	*meal_mtx;
}	t_philo;

typedef struct s_data {
	t_philo         *philos;
	int				all_ate;
	pthread_mutex_t *forks;
	pthread_mutex_t print_mtx;
	pthread_mutex_t meal_mtx;
	int             dead_flag;
} t_data;

int				args_validity(char **argv);
void			*monitor_philos(void *arg);
int				error_message(char *msg);
long			get_time(void);
unsigned int	ft_atoi(const char *str);
void			init_philo(t_data *data, char **argv, int argc);
void			init_mutex_for_forks(t_data *data, char *argv1);
void			safe_print(t_philo *philo, char *msg);
int				ft_strlen(char *str);

#endif