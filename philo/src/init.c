/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afahs <afahs@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:55:31 by afahs             #+#    #+#             */
/*   Updated: 2025/09/10 07:26:31 by afahs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (0);
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (0);
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL))
		return (0);
	if (pthread_mutex_init(&data->dead_mutex, NULL))
		return (0);
	if (pthread_mutex_init(&data->meal_mutex, NULL))
		return (0);
	return (1);
}

int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
		return (0);
	i = 0;
	while (i < data->nb_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = get_time();
		data->philos[i].left_fork_id = i;
		data->philos[i].right_fork_id = (i + 1) % data->nb_philo;
		data->philos[i].data = data;
		i++;
	}
	return (1);
}

int	init_data(t_data *data)
{
	data->start_time = get_time();
	if (!init_mutexes(data))
		return (printf("Error: Mutex initialization failed\n"), 0);
	if (!init_philos(data))
		return (printf("Error: Philosopher initialization failed\n"), 0);
	return (1);
}
