#ifndef PHILO_H
#define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
typedef struct philo
{
	int				number_philos;
	int				t_eat;
	int				t_die;
	long			start_time;
	int				id;
	int				t_sleep;
	int				t_think;
	int				n_meals;
	int				meals_eaten;
	int				*dead_flag;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*print_mtx;
	pthread_mutex_t	*death_mtx;
	pthread_mutex_t	meal_mtx;
}	t_philo;

typedef struct	s_data
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	death_mtx;
	int				dead_flag;
}	t_data;

int				cleanup(t_data data);
void			init_philo(t_data *data, char **argv, int argc, int i);
void			thinking(t_philo *philo);
void			sleeping(t_philo *philo);
void			eating(t_philo *philo);
int				args_validity(char **argv);
int				death_check(long time_since_meal, t_data *data, int i);
void			*monitor_philos(void *arg);
int				error_message(char *msg);
long			get_time(void);
int				ft_atoi(const char *str);
void			init_mutex_for_forks(t_data *data, char *argv1);
void			safe_print(t_philo *philo, char *msg);
int				ft_strlen(char *str);

#endif
