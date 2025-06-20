/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:19:53 by aamraouy          #+#    #+#             */
/*   Updated: 2025/06/20 18:23:24 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(const char *str)
{
	int		next_digit;
	long	result;

	if (!str)
		return (0);
	result = 0;
	while (*str == ' ')
		str++;
	if ((*str == '-' || *str == '+') && *(str + 1))
	{
		if (*str == '-')
			return (-1);
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		next_digit = *str - '0';
		result = result * 10 + next_digit;
		str++;
	}
	return (result);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	safe_print(t_philo *philo, char *msg)
{
	long	time;

	time = get_time();
	if (msg[0] == 'd' && msg[1] == 'i' && msg[2] == 'e' && msg[3] == 'd')
	{
		pthread_mutex_lock(philo->print_mtx);
		printf("%zu %d %s\n", time - philo->start_time, philo->id, msg);
		pthread_mutex_unlock(philo->print_mtx);
		return ;
	}
	pthread_mutex_lock(philo->death_mtx);
	if (!*philo->dead_flag)
	{
		pthread_mutex_lock(philo->print_mtx);
		printf("%zu %d %s\n", time - philo->start_time, philo->id, msg);
		pthread_mutex_unlock(philo->print_mtx);
	}
	pthread_mutex_unlock(philo->death_mtx);
}

int	checker(t_philo	*philo)
{
	pthread_mutex_lock(philo->death_mtx);
	if (*philo->dead_flag)
	{
		pthread_mutex_unlock(philo->death_mtx);
		return (1);
	}
	pthread_mutex_unlock(philo->death_mtx);
	return (0);
}

void	custom_usleep(long ms, t_philo *philo)
{
	long	start;

	start = get_time();
	while (!checker(philo))
	{
		if (get_time() - start >= ms)
			break ;
		usleep(100);
	}
}
