/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:56:47 by aamraouy          #+#    #+#             */
/*   Updated: 2025/04/04 11:09:03 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_ofphilo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		custom_sleep(1, philo);
	while (1)
	{
		if(*philo->dead_flag)
			break ;
		if (philo->id % 2 == 0)
		{
			eating(philo, 1);
			sleeping(philo);
			thinking(philo);
		}
		else
		{
			eating(philo, 0);
			sleeping(philo);
			thinking(philo);
		}
	}
	return (NULL);
}

int	create_threads(t_data *data, int i)
{
	pthread_t		monitor;

	if (pthread_create(&monitor, NULL, monitor_philos, data) != 0)
		cleanup(*data);
	while (++i < data->philos[0].number_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, routine_ofphilo, &data->philos[i]) != 0)
			cleanup(*data);
	}
	if (pthread_join(monitor, NULL) != 0)
		cleanup(*data);
	i = -1;
	while (++i < data->philos[0].number_philos)
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			cleanup(*data);
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

	if (!(argc == 5 || argc == 6))
	{
		printf("Use:./philo n_philo t_die t_eat t_sleep [n_meals]\n");
		return (1);
	}
	if (args_validity(argv) == 1)
		return (1);
	memset(&simulation, 0, sizeof(t_data));
	init_mutex_for_forks(&simulation, argv[1]);
	init_philo(&simulation, argv, argc, -1);
	if (create_threads(&simulation, -1) == 1)
	{
		printf("something goes wrong in threads management\n");
	}
	cleanup(simulation);
	free(simulation.philos);
	return (0);
}
