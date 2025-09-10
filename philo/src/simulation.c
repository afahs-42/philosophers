/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afahs <afahs@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:55:41 by afahs             #+#    #+#             */
/*   Updated: 2025/09/10 08:44:41 by afahs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	int	first_fork;
	int	second_fork;

	first_fork = philo->left_fork_id;
	second_fork = philo->right_fork_id;
	if (first_fork > second_fork)
	{
		first_fork = philo->right_fork_id;
		second_fork = philo->left_fork_id;
	}
	pthread_mutex_lock(&philo->data->forks[first_fork]);
	print_status(philo, TAKE_FORK);
	pthread_mutex_lock(&philo->data->forks[second_fork]);
	print_status(philo, TAKE_FORK);
}

void	philosopher_eat(t_philo *philo)
{
	take_forks(philo);
	print_status(philo, EATING);
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	precise_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork_id]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork_id]);
}

void	philosopher_sleep_think(t_philo *philo)
{
	print_status(philo, SLEEPING);
	precise_usleep(philo->data->time_to_sleep);
	print_status(philo, THINKING);
	if (philo->data->nb_philo % 2 == 1)
		precise_usleep(10);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		precise_usleep(philo->data->time_to_eat / 2);
	while (!is_dead(philo->data))
	{
		philosopher_eat(philo);
		if (is_dead(philo->data))
			break ;
		philosopher_sleep_think(philo);
	}
	return (NULL);
}

int	start_simulation(t_data *data)
{
	int			i;
	pthread_t	monitor_thread;

	if (pthread_create(&monitor_thread, NULL, monitor_routine, data))
		return (0);
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				philosopher_routine, &data->philos[i]))
			return (0);
		i++;
	}
	pthread_join(monitor_thread, NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	return (1);
}
