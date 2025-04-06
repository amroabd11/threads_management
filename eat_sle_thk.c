/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sle_thk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:36:08 by aamraouy          #+#    #+#             */
/*   Updated: 2025/04/05 21:06:46 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <errno.h>

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	safe_print(philo, "has taken fork\n");
	pthread_mutex_lock(philo->l_fork);
	safe_print(philo, "has taken fork\n");
	safe_print(philo, "is eating\n");
	usleep(philo->t_eat * 1000);
	pthread_mutex_lock(&philo->meal_mtx);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mtx);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	sleeping(t_philo *philo)
{
	safe_print(philo, "is sleeping\n");
	usleep(philo->t_sleep * 1000);
}

void	thinking(t_philo *philo)
{
	safe_print(philo, "is thinking\n");
}
