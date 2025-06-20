/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamraouy <aamraouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 13:45:45 by aamraouy          #+#    #+#             */
/*   Updated: 2025/06/20 18:38:26 by aamraouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	content(char *argument)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (!argument)
		return (0);
	while (argument[i])
	{
		if ((argument[i] < '0' || argument[i] > '9') && argument[i] != '+')
			return (0);
		if (argument[i] == '+')
			flag++;
		if (flag == 2)
			return (0);
		i++;
	}
	return (1);
}

int	args_validity(char **argv)
{
	if ((ft_atoi(argv[1]) <= 0 || ft_atoi(argv[1]) > 200)
		|| content(argv[1]) == 0)
		return (error_message("invalid nbr of philosophers\n"));
	if (ft_atoi(argv[2]) < 60 || content(argv[2]) == 0)
		return (error_message("invalid time to die\n"));
	if (ft_atoi(argv[3]) < 60 || content(argv[3]) == 0)
		return (error_message("invalid time to eat\n"));
	if (ft_atoi(argv[4]) < 60 || content(argv[4]) == 0)
		return (error_message("invalid time to sleep\n"));
	if (argv[5])
		if (ft_atoi(argv[5]) <= 0 || content(argv[5]) == 0)
			return (error_message("invalid number of meals\n"));
	return (0);
}

long	get_time(void)
{
	struct timeval	timevalue;

	if (gettimeofday(&timevalue, NULL) < 0)
		return (0);
	return ((timevalue.tv_sec * 1000) + (timevalue.tv_usec / 1000));
}

void	initialize_each_philo(t_data *data, char **argv, int argc, int i)
{
	int	num_philos;

	num_philos = ft_atoi(argv[1]);
	while (++i < num_philos)
	{
		data->philos[i].is_eating = 0;
		data->philos[i].id = i + 1;
		data->philos[i].number_philos = num_philos;
		data->philos[i].t_die = ft_atoi(argv[2]);
		data->philos[i].t_eat = ft_atoi(argv[3]);
		data->philos[i].t_sleep = ft_atoi(argv[4]);
		data->philos[i].n_meals = -1;
		if (argc == 6)
			data->philos[i].n_meals = ft_atoi(argv[5]);
		data->philos[i].meals_eaten = 0;
		data->philos[i].start_time = get_time();
		data->philos[i].last_meal = get_time();
		data->philos[i].print_mtx = &data->print_mtx;
		data->philos[i].death_mtx = &data->death_mtx;
		data->philos[i].dead_flag = &data->dead_flag;
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[(i + 1) % num_philos];
		pthread_mutex_init(&data->philos[i].meal_mtx, NULL);
	}
}

void	init_mutex_for_forks(t_data *data, char *argv1)
{
	int	i;
	int	num_philos;

	num_philos = ft_atoi(argv1);
	data->philos = malloc(sizeof(t_philo) * num_philos);
	if (!data->philos)
		return ;
	data->forks = malloc(sizeof(pthread_mutex_t) * num_philos);
	if (!data->forks)
		return ;
	i = -1;
	data->dead_flag = 0;
	while (++i < num_philos)
		pthread_mutex_init(&data->forks[i], NULL);
	pthread_mutex_init(&data->print_mtx, NULL);
	pthread_mutex_init(&data->death_mtx, NULL);
}
