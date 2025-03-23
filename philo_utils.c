/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 13:45:45 by aamraouy          #+#    #+#             */
/*   Updated: 2025/03/23 13:49:00 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	content(char *argument)
{
	int	i;

	i = 0;
	if (!argument)
		return (0);
	while (argument[i])
	{
		if (argument[i] < '0' || argument[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	args_validity(char **argv)
{
	if (ft_atoi(argv[1]) <= 0 || content(argv[1]) == 0)
		return(error_message("invalid nbr of philosophers\n"));
	if (ft_atoi(argv[2]) <= 0 || content(argv[2]) == 0)
		return(error_message("invalid time to die\n"));
	if (ft_atoi(argv[3]) <= 0 || content(argv[3]) == 0)
		return(error_message("invalid time to eat\n"));
	if (ft_atoi(argv[4]) <= 0 || content(argv[4]) == 0)
		return (error_message("invalid time to sleep\n"));
	if (argv[5])
		if (ft_atoi(argv[5]) <= 0 || content(argv[5]) == 0)
			return (error_message("invalid number of meals\n"));
	return (0);
}

long	get_time(void)
{
	struct timeval	timevalue;

	gettimeofday(&timevalue, NULL);
	return ((timevalue.tv_sec * 1000) + (timevalue.tv_usec / 1000)); //converts the both elements to ms and adding them to obtain the exact time as this 00.00.00
}

void	init_philo(t_data *data, char **argv, int argc)
{
	int	num_philos;
	int	i;

	i = -1;
	num_philos = ft_atoi(argv[1]);
	if (!(data->philos = malloc(sizeof(t_data) * num_philos)))
		return ;
	while (++i < num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].number_philos = num_philos;
		data->philos[i].t_die = ft_atoi(argv[2]);
		data->philos[i].t_eat = ft_atoi(argv[3]);
		data->philos[i].t_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			data->philos[i].n_meals = ft_atoi(argv[5]);
		else
			data->philos[i].n_meals = -1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = get_time();
		data->philos[i].print_mtx = &data->print_mtx;
		data->philos[i].meal_mtx = &data->meal_mtx;
		data->philos[i].dead_flag = data->dead_flag;
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[(i + 1) % num_philos];
		data->philos[i].dead_flag = data->dead_flag;
	}
}

void	init_mutex_for_forks(t_data *data, char *argv1)
{
	int	i;
	int	num_philos;

	data->dead_flag = 0;
	i = -1;
	num_philos = ft_atoi(argv1);
	data->forks = malloc(sizeof(pthread_mutex_t) * num_philos);
	if (!data->forks)
		return ;
	while (++i < num_philos)
		pthread_mutex_init(&data->forks[i], NULL);
	pthread_mutex_init(&data->print_mtx, NULL);
	pthread_mutex_init(&data->meal_mtx, NULL);
}

// int	check_dies(t_philo *philo)
// {
// 	long			time;
// 	int	i;

// 	i = -1;
	
// 	while (++i < philo->number_philos)
// 	{
// 		time = get_time() - philo->last_meal;
// 		pthread_mutex_lock(&philo->deathmutex[i]);
// 		if (time >= philo[i].t_die)
// 		{
// 			philo[i].died = 1;
// 			printf("philosopher %d died\n", philo[i].id);
// 			pthread_mutex_unlock(philo[i].deathmutex);
// 			return (1);
// 		}
// 		pthread_mutex_unlock(philo[i].deathmutex);
// 	}
// 	return (0);
// }

// void	lock_forkes(t_philo *philo)
// {
// 	int	i;

// 	i = 0;
// 	while (i < philo->number_philos)
// 	{
// 		pthread_mutex_lock();
// 	}
	
// }

