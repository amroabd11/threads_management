#include "philo.h"

int	content(char *argument)
{
	int	i;

	i = 0;
	if (!argument)
		return (0);
	while (argument[i])
	{
		if (argument[i] < '0' || argument[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	args_validity(char **argv)
{
	if (ft_atoi(argv[1]) <= 0 || content(argv[1]) == 0)
		return(error_message("invalid nbr of philosophers\n"));
	if (ft_atoi(argv[2]) <= 0 || content(argv[2]) == 0)
		return(error_message("invalid time to die\n"));
	if (ft_atoi(argv[3]) <= 0 || content(argv[3]) == 0)
		return(error_message("invalid time to eat\n"));
	if (ft_atoi(argv[4]) <= 0 || content(argv[4]) == 0)
		return (error_message("invalid time to sleep\n"));
	if (argv[5])
		if (ft_atoi(argv[5]) <= 0 || content(argv[5]) == 0)
			return (error_message("invalid number of meals\n"));
	return (0);
}

long	get_time(void)
{
	struct timeval	timevalue;

	gettimeofday(&timevalue, NULL);
	return ((timevalue.tv_sec * 1000) + (timevalue.tv_usec / 1000)); //converts the both elements to ms and adding them to obtain the exact time as this 00.00.00
}

void	init_philo(t_philo *philo, char **argv, int argc)
{
	int	num_philos;
	int	i;

	i = -1;
	num_philos = ft_atoi(argv[1]);
	while (++i < num_philos)
	{
		philo[i].id = i + 1;
		philo[i].number_philos = num_philos;
		philo[i].t_die = ft_atoi(argv[2]);
		philo[i].t_eat = ft_atoi(argv[3]);
		philo[i].t_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			philo[i].t_think = ft_atoi(argv[5]);
		else
			philo[i].t_think = -1;
		philo[i].meals_eaten = 0;
		philo[i].last_meal = get_time();
		philo[i].l_fork = &philo->forks[i];
		philo[i].r_fork = &philo->forks[(i + 1) % num_philos];
	}
}

void	init_mutex_for_forks(t_philo *philo, char *argv1)
{
	int	i;
	int	num_philos;

	philo->died = 0;
	num_philos = ft_atoi(argv1[1]);
	philo->forks = malloc(sizeof(pthread_mutex_t) * num_philos);
	if (!philo->forks)
		return ;
	while (++i < num_philos)
		pthread_mutex_init(&philo->forks[i], NULL);
	pthread_mutex_init(&philo->printing, NULL);
	pthread_mutex_init(&philo->meal_mtx, NULL);
}

int	check_dies(t_philo *philo)
{
	long			time;
	int	i;

	i = -1;
	
	while (++i < philo->number_philos)
	{
		time = get_time() - philo->last_meal;
		pthread_mutex_lock(&philo->deathmutex[i]);
		if (time >= philo[i].t_die)
		{
			philo[i].died = 1;
			printf("philosopher %d died\n", philo[i].id);
			pthread_mutex_unlock(philo[i].deathmutex);
			return (1);
		}
		pthread_mutex_unlock(philo[i].deathmutex);
	}
	return (0);
}

// void	lock_forkes(t_philo *philo)
// {
// 	int	i;

// 	i = 0;
// 	while (i < philo->number_philos)
// 	{
// 		pthread_mutex_lock();
// 	}
	
// }

