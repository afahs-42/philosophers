/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afahs <afahs@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:56:14 by afahs             #+#    #+#             */
/*   Updated: 2025/09/10 07:26:56 by afahs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	precise_usleep(long microseconds)
{
	long	start;
	long	elapsed;
	long	rem;

	start = get_time();
	while (1)
	{
		elapsed = get_time() - start;
		rem = microseconds - elapsed;
		if (rem <= 0)
			break ;
		if (rem > 1000)
			usleep(rem / 2);
		else
		{
			while (get_time() - start < microseconds)
				;
		}
	}
}

int	is_dead(t_data *data)
{
	int	dead;

	pthread_mutex_lock(&data->dead_mutex);
	dead = data->dead_flag;
	pthread_mutex_unlock(&data->dead_mutex);
	return (dead);
}

void	print_status(t_philo *philo, char *status)
{
	long	time;

	if (is_dead(philo->data))
		return ;
	pthread_mutex_lock(&philo->data->print_mutex);
	time = get_time() - philo->data->start_time;
	if (!is_dead(philo->data))
		printf("%ld %d %s\n", time, philo->id, status);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
