/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:51:50 by tjkruger          #+#    #+#             */
/*   Updated: 2025/06/10 15:38:52 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(int time_in_ms)
{
	long	start;

	start = get_current_time();
	while (get_current_time() - start < time_in_ms)
	{
		usleep(250);
	}
	return (1);
}

float	get_converted_time(long start)
{
	return ((float)(get_current_time() - start));
}

int	make_dead_mutex(t_program *program)
{
	program->dead_mutex = malloc(sizeof(pthread_mutex_t));
	if (!program->dead_mutex)
	{
		free(program->forks);
		free(program->print_mutex);
		free(program);
		return (1);
	}
	pthread_mutex_init(program->dead_mutex, NULL);
	return (0);
}
