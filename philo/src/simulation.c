/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afahs <afahs@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:55:41 by afahs             #+#    #+#             */
/*   Updated: 2025/09/10 03:56:44 by afahs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[philo->right_fork_id]);
		print_status(philo, TAKE_FORK);
		pthread_mutex_lock(&philo->data->forks[philo->left_fork_id]);
		print_status(philo, TAKE_FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork_id]);
		print_status(philo, TAKE_FORK);
		pthread_mutex_lock(&philo->data->forks[philo->right_fork_id]);
		print_status(philo, TAKE_FORK);
	}
}

void	philospher_eat(t_philo *philo)
{
	take_forks(philo);
	print_status(philo, EATING);
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = get_time();
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
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		precise_usleep(philo->data->time_to_eat / 2);
}
