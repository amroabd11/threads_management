/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sle_thk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:36:08 by aamraouy          #+#    #+#             */
/*   Updated: 2025/04/17 15:42:12 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	if (philo->id == philo->number_philos)
	{
		pthread_mutex_lock(philo->l_fork);
		safe_print(philo, "has taken fork");
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		safe_print(philo, "has taken fork");
	}
	pthread_mutex_lock(&philo->meal_mtx);
	philo->is_eating = 1;
	philo->meals_eaten++;
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_mtx);
	safe_print(philo, "is eating");
	usleep(philo->t_eat * 1000);
	pthread_mutex_lock(&philo->meal_mtx);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->meal_mtx);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	sleeping(t_philo *philo)
{
	safe_print(philo, "is sleeping");
	usleep(philo->t_sleep * 1000);
}

void	thinking(t_philo *philo)
{
	safe_print(philo, "is thinking");
}
