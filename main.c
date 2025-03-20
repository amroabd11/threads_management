/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:56:47 by aamraouy          #+#    #+#             */
/*   Updated: 2025/03/20 10:43:17 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	followed_instructions(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_mtx);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_mtx);
	safe_print(philo, "is eating\n");
	usleep(philo->t_eat * 1000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	safe_print(philo, "is sleeping\n");
	usleep(philo->t_sleep * 1000);
	safe_print(philo, "is thinking\n");
}

void	*routine_ofphilo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->died)
			break;
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->r_fork);
			safe_print(philo, "has taken right fork\n");
			pthread_mutex_lock(philo->l_fork);
			safe_print(philo, "has taken left fork\n");
		}
		else
		{
			pthread_mutex_lock(philo->l_fork);
			safe_print(philo, "has taken left fork\n");
			pthread_mutex_lock(philo->r_fork);
			safe_print(philo, "has taken right fork\n");
		}
		followed_instructions(philo);
	}
	return (NULL);
}

int	create_threads(t_philo *philo)
{
	int	i;
	pthread_t		*threads;
	pthread_t		*monitor;

	threads = malloc(sizeof(pthread_t) * philo->number_philos);
	if (!threads)
		return (1);
	i = -1;
	while (++i < philo->number_philos)
	{
		if (pthread_create(&threads[i], NULL, routine_ofphilo, &philo[i]) != 0)
			return (1);
	}
	i = -1;
	pthread_create(&monitor, NULL, monitor_philos, &philo);//construct the function TODO
	pthread_join(monitor, NULL);
	while (++i < philo->number_philos)
		pthread_join(threads[i], NULL);
	free(threads);
	return (0);
}

int	threads_managing(t_philo *philo)
{
	int	i;

	i = 0;
	if (create_threads(philo) == 1)
	{
		free(philo->forks);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;

	if (!(argc == 5 || argc == 6))
	{
		printf("Use:./philo n_philo t_die t_eat t_sleep [n_meals]\n");
		return (1);
	}
	if (args_validity(argv) == 1)
		return (1);
	philo = (t_philo *)malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!philo)
		return (1);
	init_mutex_for_forks(philo, argv[1]);
	init_philo(philo, argv, argc);
	if (threads_managing(philo) == 1)
		printf("something goes wrong in threads and mutexes management\n");
	return (0);
}
