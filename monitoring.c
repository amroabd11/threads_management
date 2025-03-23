/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:10:26 by aamraouy          #+#    #+#             */
/*   Updated: 2025/03/23 15:25:32 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_philo_meals(t_data *data, int *all_ate, int i)
{
	*all_ate = 0;
	if (data->philos[i].n_meals != -1 && data->philos[i].meals_eaten >= data->philos[i].n_meals)
		*all_ate++;
}

int	stop_routine(t_data *data, int *all_ate)
{
	if (data->philos->number_philos == *all_ate)
	{
		pthread_mutex_lock(&data->print_mtx);
		printf("all philos ate\n");
		data->dead_flag = 1;
		pthread_mutex_unlock(&data->print_mtx);
		return (0);
	}
	*all_ate = 0;
	return (1);
}

void	*monitor_philos(void *arg)
{
	int		i;
	t_data *data;

	data = (t_data *)arg;
	while (1)
	{
		i = -1;
		while (++i < data->philos->number_philos)
		{
			if(get_time() - data->philos[i].last_meal > data->philos[i].t_die
				|| data->philos[i].meals_eaten >= data->philos->n_meals)
			{
				pthread_mutex_lock(data->philos[i].print_mtx);
				printf("%ld %d died\n", get_time()
						- data->philos[i].last_meal, data->philos[i].id);
				data->dead_flag = 1;
				pthread_mutex_unlock(data->philos[i].print_mtx);
				return (NULL);
			}
			check_philo_meals(data, &data->all_ate, i);
		}
		if (!stop_routine(data, &data->all_ate))
			return (NULL);
		usleep(100);
	}
}
