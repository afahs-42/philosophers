/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afahs <afahs@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:55:51 by afahs             #+#    #+#             */
/*   Updated: 2025/09/10 07:26:40 by afahs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philosopher_died(t_philo *philo)
{
	long	current_time;

	pthread_mutex_lock(&philo->data->meal_mutex);
	current_time = get_time();
	if (current_time - philo->last_meal_time >= philo->data->time_to_die)
	{
		pthread_mutex_unlock(&philo->data->meal_mutex);
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%ld %d %s\n", current_time - philo->data->start_time,
			philo->id, DIED);
		pthread_mutex_unlock(&philo->data->print_mutex);
		pthread_mutex_lock(&philo->data->dead_mutex);
		philo->data->dead_flag = 1;
		pthread_mutex_unlock(&philo->data->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->meal_mutex);
	return (0);
}

int	check_death(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (philosopher_died(&data->philos[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_all_ate(t_data *data)
{
	int	i;
	int	finished_eating;

	if (data->nb_meals == -1)
		return (0);
	finished_eating = 0;
	pthread_mutex_lock(&data->meal_mutex);
	i = 0;
	while (i < data->nb_philo)
	{
		if (data->philos[i].meals_eaten >= data->nb_meals)
			finished_eating++;
		i++;
	}
	pthread_mutex_unlock(&data->meal_mutex);
	if (finished_eating == data->nb_philo)
	{
		pthread_mutex_lock(&data->dead_mutex);
		data->all_ate_flag = 1;
		pthread_mutex_unlock(&data->dead_mutex);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_death(data) || check_all_ate(data))
			break ;
		usleep(1000);
	}
	return (NULL);
}
