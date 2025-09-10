/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afahs <afahs@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 08:52:11 by afahs             #+#    #+#             */
/*   Updated: 2025/09/10 08:52:13 by afahs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>
# include <semaphore.h>
# include <fcntl.h>
# include <string.h>

# define TAKE_FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"

typedef struct s_data
{
	int		nb_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		nb_meals;
	long	start_time;
	pid_t	*pids;
	sem_t	*forks;
	sem_t	*print_sem;
	sem_t	*death_sem;
}	t_data;

typedef struct s_philo
{
	int		id;
	int		meals_eaten;
	long	last_meal_time;
	t_data	*data;
}	t_philo;

/* parsing_bonus.c */
int		parse_arguments(int argc, char **argv, t_data *data);
int		ft_atoi(const char *str);
int		is_valid_number(const char *str);

/* init_bonus.c */
int		init_data(t_data *data);
int		init_semaphores(t_data *data);

/* simulation_bonus.c */
int		start_simulation(t_data *data);
void	philosopher_process(int id, t_data *data);
void	*monitor_thread(void *arg);

/* utils_bonus.c */
long	get_time(void);
void	precise_usleep(long microseconds);
void	print_status(t_philo *philo, char *status, int death);

/* cleanup_bonus.c */
void	cleanup_data(t_data *data);
void	kill_all_processes(t_data *data);

#endif