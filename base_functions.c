/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:19:53 by aamraouy          #+#    #+#             */
/*   Updated: 2025/04/04 10:46:29 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	ft_atoi(const char *str)
{
		unsigned int	sign;
		unsigned int	next_digit;
		unsigned int	result;

		sign = 1;
		result = 0;
		if(!str)
			return (0);
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
		return (result * sign);
}

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	safe_print(t_philo *philo, char *msg)
{
	size_t	time;

	pthread_mutex_lock(philo->print_mtx);
	time = get_time();
	if (!*philo->dead_flag)
		printf("%zu %d %s\n", time - philo->start_time, philo->id, msg);
	pthread_mutex_unlock(philo->print_mtx);
}

void	custom_sleep(long ms, t_philo *philo)
{
	long	start;

	start = get_time();
	while (get_time() - start < ms)
	{
		usleep(100);
		pthread_mutex_lock(philo->death_mtx);
		if (*philo->dead_flag)
		{
			pthread_mutex_unlock(philo->death_mtx);
			break ;
		}
		pthread_mutex_unlock(philo->death_mtx);
	}
}
