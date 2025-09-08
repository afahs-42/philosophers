/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afahs <afahs@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:55:16 by afahs             #+#    #+#             */
/*   Updated: 2025/09/08 16:25:33 by afahs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	ft_atoi(const char *str)
{
	int	i;
	int	s;
	int	n;

	i = 0;
	s = 1;
	n = 0;
	while ((str[i] > 8 && str[i] < 14) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			s = s * -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		n = (n * 10) + (str[i] - '0');
		i++;
	}
	return (n * s);
}

int	is_valid_number(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	validate_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (printf("Usage: ./philo int int int int [int]\n"), 0);
	i = 1;
	while (i < argc)
	{
		if (!is_valid_number(argv[i]) || ft_atoi(argv[i]) <= 0)
			return (printf("Error: Invalid arg %s", argv[i]), 0);
		i++;
	}
	if (ft_atoi(argv[1] > 200))
		return (printf("Error to many philos [max 200]"), 0);
	return (1);
}

int	parse_arguments(int argc, char **argv, t_data *data)
{
	if (!validate_args(argc, argv))
		return (0);
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nb_meals = ft_atoi(argv[5]);
	data->dead_flag = 0;
	data->all_ate_flag = 0;
	return (0);
}
