/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:56:47 by aamraouy          #+#    #+#             */
/*   Updated: 2025/04/05 21:09:41 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_ofphilo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->id % 2 == 0)
			usleep(500);
		if (*philo->dead_flag)
			break ;
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

int	create_threads(t_data *data, int i)
{
	pthread_t		monitor;

	while (++i < data->philos[0].number_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				routine_ofphilo, &data->philos[i]) != 0)
			return (cleanup(*data));
	}
	if (pthread_create(&monitor, NULL, monitor_philos, data) != 0)
		return (cleanup(*data));
	if (pthread_join(monitor, NULL) != 0)
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
	t_philo	philos[600];

	simulation.philos = philos;
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
		printf("something goes wrong in threads management\n");
	cleanup(simulation);
	free(simulation.forks);
	return (0);
}
