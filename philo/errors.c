/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 10:48:08 by aamraouy          #+#    #+#             */
/*   Updated: 2025/06/20 13:22:25 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_message(char *msg)
{
	write(1, msg, ft_strlen(msg));
	return (1);
}

int	cleanup(t_data data)
{
	int	i;

	i = 0;
	while (i < data.philos->number_philos)
	{
		pthread_mutex_destroy(&data.forks[i]);
		pthread_mutex_destroy(&data.philos[i].meal_mtx);
		// pthread_mutex_destroy(data.philos[i].l_fork);
		// pthread_mutex_destroy(data.philos[i].r_fork);
		i++;
	}
	free(data.philos);
	free(data.forks);
	// pthread_mutex_destroy(&data.print_mtx);
	// pthread_mutex_destroy(&data.death_mtx);
	return (1);
}
