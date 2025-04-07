/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:19:53 by aamraouy          #+#    #+#             */
/*   Updated: 2025/04/07 15:03:59 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(const char *str)
{
	int		next_digit;
	long	result;

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

	pthread_mutex_lock(philo->print_mtx);
	time = get_time();
	if (!*philo->dead_flag)
		printf("%zu %d %s\n", time - philo->start_time, philo->id, msg);
	pthread_mutex_unlock(philo->print_mtx);
}
