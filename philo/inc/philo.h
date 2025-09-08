/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afahs <afahs@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:56:59 by afahs             #+#    #+#             */
/*   Updated: 2025/09/08 16:05:18 by afahs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

# define TAKE_FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	int				left_fork_id;
	int				right_fork_id;
	pthread_t		thread;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nb_meals;
	long			start_time;
	int				dead_flag;
	int				all_ate_flag;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	meal_mutex;
	t_philo			*philos;
}	t_data;

/* parsing.c */
int		parse_arguments(int argc, char **argv, t_data *data);
int		ft_atoi(const char *str);
int		is_valid_number(const char *str);

/* init.c */
int		init_data(t_data *data);
int		init_mutexes(t_data *data);
int		init_philos(t_data *data);

/* simulation.c */
int		start_simulation(t_data *data);
void	*philosopher_routine(void *arg);
void	philosopher_eat(t_philo *philo);
void	philosopher_sleep_think(t_philo *philo);

/* monitor.c */
void	*monitor_routine(void *arg);
int		check_death(t_data *data);
int		check_all_ate(t_data *data);

/* utils.c */
long	get_time(void);
void	precise_usleep(long microseconds);
void	print_status(t_philo *philo, char *status);
int		is_dead(t_data *data);

/* cleanup.c */
void	cleanup_data(t_data *data);
void	destroy_mutexes(t_data *data);

#endif
