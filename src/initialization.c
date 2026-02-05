/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:52:28 by tjkruger          #+#    #+#             */
/*   Updated: 2026/02/05 14:30:00 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_dead_mutex(t_process *process)
{
	process->dead_mutex = malloc(sizeof(pthread_mutex_t));
	if (!process->dead_mutex)
	{
		free(process->printout_mutex);
		free(process->forks);
		free(process);
		return (1);
	}
	pthread_mutex_init(process->dead_mutex, NULL);
	return (0);
}

int	init_process(char **argv, t_process *process)
{
	if (!process)
		return (1);
	process->cur_num_of_philos = ft_atoi(argv[1]);
	process->die_time = ft_atoi(argv[2]);
	process->eat_time = ft_atoi(argv[3]);
	process->sleep_time = ft_atoi(argv[4]);
	process->dead = 0;
	process->forks = malloc(sizeof(pthread_mutex_t)
			* process->cur_num_of_philos);
	if (!process->forks)
	{
		free(process);
		return (1);
	}
	process->printout_mutex = malloc(sizeof(pthread_mutex_t));
	if (!process->printout_mutex)
	{
		free(process->forks);
		free(process);
		return (1);
	}
	pthread_mutex_init(process->printout_mutex, NULL);
	return (init_dead_mutex(process));
}

void	cleanup_process(t_process *process, int fork_count)
{
	while (--fork_count >= 0)
		pthread_mutex_destroy(&process->forks[fork_count]);
	pthread_mutex_destroy(process->printout_mutex);
	pthread_mutex_destroy(process->dead_mutex);
	free(process->forks);
	free(process->printout_mutex);
	free(process->dead_mutex);
	free(process->philos);
	free(process);
}
