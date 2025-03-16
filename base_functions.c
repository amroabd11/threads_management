#include "philo.h"

unsigned int	ft_atoi(const char *str)
{
		unsigned int	sign;
		unsigned int	next_digit;
		unsigned int	result;

		sign = 1;
		result = 0;
		while (*str == ' ')
				str++;
		if ((*str == '-' || *str == '+') && *(str + 1))
		{
				if (*str == '-')
						sign = -1;
				str++;
		}
		while (*str >= '0' && *str <= '9')
		{
				if ((result * sign) > 10000 || (result * sign) <= 0)
						return (-1);
				next_digit = *str - '0';
				result = result * 10 + next_digit;
				str++;
		}
		return (result * sign);
}
