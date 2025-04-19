/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:10:26 by aamraouy          #+#    #+#             */
/*   Updated: 2025/04/17 15:32:36 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo_meals(t_data *data, int i)
{
	int	all_ate;

	all_ate = 0;
	while (++i < data->philos[0].number_philos)
	{
		pthread_mutex_lock(&data->philos[i].meal_mtx);
		if (data->philos[i].n_meals != -1
			&& data->philos[i].meals_eaten >= data->philos[i].n_meals)
			all_ate++;
		pthread_mutex_unlock(&data->philos[i].meal_mtx);
	}
	if (all_ate == data->philos[0].number_philos)
	{
		pthread_mutex_lock(&data->death_mtx);
		data->dead_flag = 1;
		pthread_mutex_unlock(&data->death_mtx);
		return (1);
	}
	return (0);
}

int	death_check(long time_since_meal, t_data *data, int i)
{
	int is_philo_eating;

	pthread_mutex_lock(&data->philos[i].meal_mtx);
	time_since_meal = get_time() - data->philos[i].last_meal;
	is_philo_eating = data->philos[i].is_eating;
	pthread_mutex_unlock(&data->philos[i].meal_mtx);
	if (time_since_meal > data->philos[i].t_die && is_philo_eating == 0)
	{
		if (!data->dead_flag)
		{
			pthread_mutex_lock(&data->death_mtx);
			data->dead_flag = 1;
			pthread_mutex_unlock(&data->death_mtx);
			safe_print(&data->philos[i], "died");
		}
		return (1);
	}
	return (0);
}

void	*monitor_philos(void *arg)
{
	t_data	*data;
	long	time_since_meal;
	int		i;

	time_since_meal = 0;
	data = (t_data *)arg;
	while (1)
	{
		i = -1;
		while (++i < data->philos[0].number_philos)
		{
			if (death_check(time_since_meal, data, i))
				return (NULL);
		}
		if (check_philo_meals(data, -1))
			return (NULL);
	}
	return (arg);
}
