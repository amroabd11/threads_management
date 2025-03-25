/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:10:26 by aamraouy          #+#    #+#             */
/*   Updated: 2025/03/25 16:38:13 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo_meals(t_data *data, int i, int *meals)
{
	int	all_ate;

	all_ate = 0;
	while (++i < data->philos->number_philos)
	{
		if (data->philos[i].n_meals != -1 &&
		meals[i] >= data->philos[i].n_meals)
			all_ate++;
	}
	if (all_ate == data->philos->number_philos)
	{
		// pthread_mutex_lock(&data->print_mtx);
		printf("all philos ate\n");
		// pthread_mutex_unlock(&data->print_mtx);
		pthread_mutex_lock(&data->death_mtx);//TODO
		data->dead_flag = 1;
		pthread_mutex_unlock(&data->death_mtx);
		return (0);
	}
	return (1);
}

int	death_check(long time_since_meal, t_data *data, int i)
{
	if (time_since_meal >= data->philos[i].t_die)
	{
		// pthread_mutex_lock(&data->death_mtx);//TODO
		if (!data->dead_flag)
		{
		  data->dead_flag = 1;
		//   pthread_mutex_lock(&data->print_mtx);
		  printf("%ld %d died\n", get_time() - data->philos[i].start_time, data->philos[i].id);
		//   pthread_mutex_unlock(&data->print_mtx);
		}
		// pthread_mutex_unlock(&data->death_mtx);
		return (1);
	}
	return (0);
}

void	*monitor_philos(void *arg)
{
	int		i;
	t_data *data;
	long	time_since_meal;
	int		*meals;

	data = (t_data *)arg;
	meals = malloc(data->philos->number_philos);
	while (1)
	{
		if (data->dead_flag)
			return (NULL);
		i = -1;
		while (++i < data->philos->number_philos)
		{
			pthread_mutex_lock(&data->meal_mtx);
			time_since_meal = get_time() - data->philos[i].last_meal;
			meals[i] = data->philos[i].meals_eaten; //check for every thread 	
			pthread_mutex_unlock(&data->meal_mtx);
			if (death_check(time_since_meal, data, i))
				return (free(meals), NULL);
		}
		if (!check_philo_meals(data, -1, meals))
			return (NULL);
	}
}
