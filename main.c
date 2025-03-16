#include "philo.h"

void	*routine_ofphilo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->forks[philo->l_fork]);
		print_routine(philo, "has taken a fork");
		pthread_mutex_lock(&philo->forks[philo->r_fork]);
		print_routine(philo, "has taken a fork");
		print_routine(philo, "is eating");
		philo->last_meal = get_time();
		usleep(philo->t_eat * 1000);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->forks[philo->r_fork]);
		
	}
	
}

void	create_threads(t_philo *philo)
{
	int	i;
	pthread_t	*threads;

	threads = malloc(sizeof(pthread_t) * philo->number_philos);
	if (!threads)
		perror("malloc ");
	i = 0;
	while (i < philo->number_philos)
	{
		philo[i].start_time = get_time_ms();
		philo[i].last_meal = get_time_ms();
		philo[i].meals_eaten = 0;
		philo[i].id = i + 1;
		philo[i].l_fork  = i;
		philo[i].r_fork = (i + 1) % philo->number_philos;
		if (pthread_create(&threads[i], NULL, routine_ofphilo, &philo[i]) != 0)
			exit(EXIT_FAILURE);//msg failure in thread creation
		i++;
	}
	i = 0;
	while (i < philo->number_philos)
	{
		pthread_join(threads[i++], NULL);
	}
	free(threads);
}

void	threads_and_mutexes(t_philo *philo)
{
	int	i;

	i = 0;
	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->number_philos);
	if (!philo->forks)
		exit(1);
	while (i < philo->number_philos)
	{
		pthread_mutex_init(&philo->forks[i], NULL);
		i++;
	}
	create_threads(philo);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;

	if (argc != 5 || argc != 6)
		return (error_message("Usage:./philo num_philo t_die t_eat t_sleep [num_meals]\n"));
	args_validity(argv);
	philo = (t_philo *)malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!philo)
		return (1);
	init_philo_stuff(philo, argv, argc);
	threads_and_mutexes(philo);
	// lock_forkes(philo);
}
