/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clock.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:51:50 by tjkruger          #+#    #+#             */
/*   Updated: 2025/07/07 13:47:30 by tjkruger         ###   ########.fr       */
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
		usleep(250);
	return (1);
}

float	get_converted_time(long start)
{
	return ((float)(get_current_time() - start));
}

int	make_dead_mutex(t_process *process)
{
	process->dead_mutex = malloc(sizeof(pthread_mutex_t));
	if (!process->dead_mutex)
	{
		free(process->forks);
		free(process->print_mutex);
		free(process);
		return (1);
	}
	pthread_mutex_init(process->dead_mutex, NULL);
	return (0);
}
