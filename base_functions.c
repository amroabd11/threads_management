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

int	limits_of_dying(t_philo *philo)
{
	pthread_mutex_lock(philo->deathmutex);
	if(philo->died == 1)
	{
		pthread_mutex_unlock(philo->deathmutex);
		return (1);
	}
	pthread_mutex_unlock(philo->deathmutex);
	if(philo->n_meals > 0 && philo->meals_eaten >= philo->n_meals)
		return (1);
	return 0;
}

void	safe_print(t_philo *philo, char *msg)
{
	size_t	time;

	pthread_mutex_lock(philo->printing);
	time = get_time() - philo->s_time;
	if (!check_dies(philo))
		printf("%zu %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(philo->printing);
}