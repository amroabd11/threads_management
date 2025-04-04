/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sle_thk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:36:08 by aamraouy          #+#    #+#             */
/*   Updated: 2025/04/03 10:47:08 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo, int i)
{
	if (i == 1)
	{
		pthread_mutex_lock(philo->r_fork);
		safe_print(philo, "has taken right fork\n");
		pthread_mutex_lock(philo->l_fork);
		safe_print(philo, "has taken left fork\n");
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		safe_print(philo, "has taken left fork\n");
		pthread_mutex_lock(philo->r_fork);
		safe_print(philo, "has taken right fork\n");
	}
	safe_print(philo, "is eathing\n");
	pthread_mutex_lock(philo->meal_mtx);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_mtx);
	custom_sleep(philo->t_eat, philo);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	sleeping(t_philo *philo)
{
	safe_print(philo, "is sleeping\n");
	custom_sleep(philo->t_sleep, philo);
}

void	thinking(t_philo *philo)
{
	safe_print(philo, "is thinking\n");
}
