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
	time = get_time() - philo->last_meal;
	if (!philo->dead_flag)
		printf("%zu %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(philo->print_mtx);
}