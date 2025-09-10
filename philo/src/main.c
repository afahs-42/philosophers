/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afahs <afahs@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:02:56 by afahs             #+#    #+#             */
/*   Updated: 2025/09/10 07:26:36 by afahs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (!parse_arguments(argc, argv, &data))
		return (1);
	if (!init_data(&data))
		return (cleanup_data(&data), 1);
	if (data.nb_philo == 1)
	{
		printf("0 1 %s\n", TAKE_FORK);
		precise_usleep(data.time_to_die);
		printf("%ld 1 %s\n", data.time_to_die, DIED);
		cleanup_data(&data);
		return (0);
	}
	if (!start_simulation(&data))
		return (cleanup_data(&data), 1);
	cleanup_data(&data);
	return (0);
}
