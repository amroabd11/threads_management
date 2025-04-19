/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:56:47 by aamraouy          #+#    #+#             */
/*   Updated: 2025/04/17 15:30:42 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	action(t_philo *philo)
{
	eating(philo);
	sleeping(philo);
	thinking(philo);
}

void	*routine_ofphilo(void *arg)
{
	t_philo	*philo;
	int is_dead;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->death_mtx);
	is_dead = *philo->dead_flag;
	pthread_mutex_unlock(philo->death_mtx);
	if (philo->id % 2 == 0)
		usleep(500);
	while (!is_dead)
	{
		if (philo->id == philo->number_philos && philo->number_philos != 1)
		{
			pthread_mutex_lock(philo->r_fork);
			safe_print(philo, "has taken fork");
		}
		else
		{
			pthread_mutex_lock(philo->l_fork);
			safe_print(philo, "has taken fork");
		}
		action(philo);
	}
	return (NULL);
}

int	create_threads(t_data *data, int i)
{
	pthread_t		monitor;

	if (pthread_create(&monitor, NULL, monitor_philos, data) != 0)
		return (cleanup(*data));
	while (++i < data->philos[0].number_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				routine_ofphilo, &data->philos[i]) != 0)
			return (cleanup(*data));
	}
	if (pthread_join(monitor, NULL) != 0)
		return (cleanup(*data));
	i = -1;
	while (++i < data->philos[0].number_philos)
		if (pthread_detach(data->philos[i].thread) != 0)
			return (cleanup(*data));
	return (0);
}

int	cleanup(t_data data)
{
	int	i;

	i = 0;
	while (i < data.philos->number_philos)
	{
		pthread_mutex_destroy(&data.forks[i]);
		pthread_mutex_destroy(&data.philos[i].meal_mtx);
		i++;
	}
	pthread_mutex_destroy(&data.print_mtx);
	pthread_mutex_destroy(&data.death_mtx);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	simulation;

	if (!(argc == 5 || argc == 6))
	{
		printf("Use:./philo n_philo t_die t_eat t_sleep [n_meals]\n");
		return (1);
	}
	if (args_validity(argv) == 1)
		return (1);
	init_mutex_for_forks(&simulation, argv[1]);
	init_philo(&simulation, argv, argc, -1);
	if (create_threads(&simulation, -1) == 1)
	{
		printf("error in threads management\n");
		return (EXIT_FAILURE);
	}
	return (0);
}
