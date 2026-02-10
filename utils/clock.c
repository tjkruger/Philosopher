/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clock.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:51:50 by tjkruger          #+#    #+#             */
/*   Updated: 2026/02/10 17:14:35 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

float	get_converted_time(long start)
{
	long	current;

	current = get_time();
	return ((float)(current - start));
}

int	ft_usleep(int time_in_ms)
{
	long	start;

	start = get_time();
	while (get_time() - start < time_in_ms)
		usleep(100);
	return (1);
}

int	make_dead_mutex(t_process *process)
{
	process->dead_mutex = malloc(sizeof(pthread_mutex_t));
	if (!process->dead_mutex)
	{
		free(process->forks);
		free(process->printout_mutex);
		free(process);
		return (1);
	}
	pthread_mutex_init(process->dead_mutex, NULL);
	return (0);
}
