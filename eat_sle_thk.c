/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sle_thk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:36:08 by aamraouy          #+#    #+#             */
/*   Updated: 2025/04/24 10:04:41 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mtx);
	philo->is_eating = 1;
	philo->meals_eaten++;
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_mtx);
	safe_print(philo, "is eating");
	ft_usleep(philo->t_eat, philo);
	pthread_mutex_lock(&philo->meal_mtx);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->meal_mtx);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	sleeping(t_philo *philo)
{
	safe_print(philo, "is sleeping");
	ft_usleep(philo->t_sleep , philo);
}

void	thinking(t_philo *philo)
{
	safe_print(philo, "is thinking");
}
