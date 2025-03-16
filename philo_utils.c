#include "philo.h"

int	content(char *argument)
{
	int	i;

	i = 0;
	while (argument[i])
	{
		if (argument[i] < '0' || argument[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	args_validity(char **argv)
{
	if (ft_atoi(argv[1]) <= 0 && content(argv[1]) == 0)
		exit(error_message("invalid nbr of philosophers\n"));
	if (ft_atoi(argv[2]) <= 0 && content(argv[2]) == 0)
		exit(error_message("invalid time for die\n"));
	if (ft_atoi(argv[3]) <= 0 && content(argv[3]) == 0)
		exit(error_message("invalid time to eat"));
	if (ft_atoi(argv[4]) <= 0 && content(argv[4]) == 0)
		exit(error_message("invalid time to sleep\n"));
	if (ft_atoi(argv[5]) <= 0 && content(argv[5]) == 0)
		exit(error_message("invalid n of times each philo must eat\n"));
	return ;
}

void	init_philo_stuff(t_philo *philo, char **argv, int argc)
{
	philo->number_philos = ft_atoi(argv[1]);
	philo->t_die = ft_atoi(argv[2]);
	philo->t_eat = ft_atoi(argv[3]);
	philo->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->n_meals = ft_atoi(argv[5]);//optional
	else
		philo->n_meals = -1;
	return ;
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
