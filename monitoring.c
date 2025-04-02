/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:10:26 by aamraouy          #+#    #+#             */
/*   Updated: 2025/03/28 18:32:14 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo_meals(t_data *data, int i, int *meals)
{
	int	all_ate;

	all_ate = 0;
	while (++i < data->philos[0].number_philos)
	{
		if (data->philos[i].n_meals != -1 &&
		meals[i] >= data->philos[i].n_meals)
			all_ate++;
	}
	if (all_ate == data->philos->number_philos)
	{
		printf("all philos ate\n");
		pthread_mutex_lock(&data->death_mtx);//TODO
		data->dead_flag = 1;
		pthread_mutex_unlock(&data->death_mtx);
		return (0);
	}
	return (1);
}

int	death_check(long time_since_meal, t_data *data, int i)
{
	// printf("time since _meal : %ld\n", time_since_meal);
	if (time_since_meal >= data->philos[i].t_die)
	{
		if (!data->dead_flag)
		{
			pthread_mutex_lock(&data->death_mtx);
			data->dead_flag = 1;
			printf("%ld %d died\n", get_time() - data->philos[i].start_time, data->philos[i].id);
			pthread_mutex_unlock(&data->death_mtx);
		}
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
	meals = malloc(4 * data->philos[0].number_philos);
	while (1)
	{
		// pthread_mutex_lock(&data->death_mtx);
		// if (data->dead_flag)
		// {
			// pthread_mutex_unlock(&data->death_mtx);
			// break ;
		// }			
		// pthread_mutex_unlock(&data->death_mtx);
		i = -1;
		while (++i < data->philos[0].number_philos)
		{
			// pthread_mutex_lock(&data->meal_mtx);
			time_since_meal = get_time() - data->philos[i].last_meal;
			meals[i] = data->philos[i].meals_eaten; //check for every thread 	
			// pthread_mutex_unlock(&data->meal_mtx);
			if (death_check(time_since_meal, data, i))
				return (NULL);
		}
		if (!check_philo_meals(data, -1, meals))
			return (NULL);
	}
	return (NULL);
}
