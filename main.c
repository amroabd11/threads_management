/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:56:47 by aamraouy          #+#    #+#             */
/*   Updated: 2025/06/11 21:18:40 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo_done_eating(t_philo *philo)
{
	int	done_eating;

	pthread_mutex_lock(&philo->meal_mtx);
	if (philo->meals_eaten == philo->n_meals)
		done_eating = 1;
	else
		done_eating = 0;
	pthread_mutex_unlock(&philo->meal_mtx);
	return (done_eating);
}

void	action(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mtx);
	philo->is_eating = 1;
	philo->meals_eaten++;
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_mtx);
	safe_print(philo, "is eating");
	custom_usleep(philo->t_eat, philo);
	pthread_mutex_lock(&philo->meal_mtx);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->meal_mtx);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	safe_print(philo, "is sleeping");
	custom_usleep(philo->t_sleep, philo);
	safe_print(philo, "is thinking");
}

void	*thread_ofphilo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		custom_usleep(200, philo);
	while (1)
	{
		if (checker(philo))
			break ;
		pthread_mutex_lock(philo->l_fork);
		safe_print(philo, "has taken a fork");
		if (philo->number_philos == 1)
		{
			custom_usleep(philo->t_die, philo);
			pthread_mutex_unlock(philo->l_fork);
			break ;
		}
		pthread_mutex_lock(philo->r_fork);
		safe_print(philo, "has taken a fork");
		action(philo);
		if (check_philo_done_eating(philo) == 1)
			break ;
	}
	return (NULL);
}

int	create_philos(t_data *data, int i)
{
	pthread_t		monitor;

	while (++i < data->philos[0].number_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				thread_ofphilo, &data->philos[i]) != 0)
			return (cleanup(*data));
	}
	if (pthread_create(&monitor, NULL, monitor_philos, data) != 0)
		return (cleanup(*data));
	if (pthread_join(monitor, NULL) != 0)
		return (cleanup(*data));
	i = -1;
	while (++i < data->philos[0].number_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (cleanup(*data));
	}
	return (0);
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
	initialize_each_philo(&simulation, argv, argc, -1);
	if (create_philos(&simulation, -1) == 1)
	{
		printf("error in threads management\n");
		return (EXIT_FAILURE);
	}
	return (0);
}
