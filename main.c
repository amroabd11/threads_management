/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:56:47 by aamraouy          #+#    #+#             */
/*   Updated: 2025/03/23 15:26:38 by aamraouy         ###   ########.fr       */
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
	if(philo->id % 2 == 0)
		usleep(1);
	while (1)
	{
		if (philo->dead_flag)
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

int	create_threads(t_data *data)
{
	int	i;
	pthread_t		*threads;
	pthread_t		monitor;

	threads = malloc(sizeof(pthread_t) * data->philos->number_philos);
	if (!threads)
		return (1);
	i = -1;
	while (++i < data->philos->number_philos)
	{
		if (pthread_create(&threads[i], NULL, routine_ofphilo, &data->philos[i]) != 0)
			return (1);
	}
	i = -1;
	pthread_create(&monitor, NULL, monitor_philos, data);//construct the function TODO
	pthread_join(monitor, NULL);
	while (++i < data->philos->number_philos)
		pthread_join(threads[i], NULL);
	free(threads);
	return (0);
}

void	cleanup(t_data data)
{
	int	i;

	i = 0;
	while (i < data.philos->number_philos)
	{
		pthread_mutex_destroy(&data.forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data.print_mtx);
	pthread_mutex_destroy(&data.meal_mtx);
}

int	main(int argc, char **argv)
{
	t_data	simulation;

	// simulation = malloc(sizeof(t_data));
	if (!(argc == 5 || argc == 6))
	{
		printf("Use:./philo n_philo t_die t_eat t_sleep [n_meals]\n");
		return (1);
	}
	if (args_validity(argv) == 1)
		return (1);
	init_mutex_for_forks(&simulation, argv[1]);//done
	init_philo(&simulation, argv, argc);
	simulation.all_ate = 0;
	if (create_threads(&simulation) == 1)
	{
		printf("something goes wrong in threads management\n");
		// free(simulation->forks);
	}
	exit(1);
	cleanup(simulation);
	// free(philo->forks);
	// free(philo);
	return (0);
}
