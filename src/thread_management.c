/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:52:42 by tjkruger          #+#    #+#             */
/*   Updated: 2026/02/10 17:13:47 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	create_philosopher_threads(t_process *process, pthread_t *threads,
		long time)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < process->cur_num_of_philos)
	{
		philo = &process->philos[i];
		philo->name = i;
		philo->thread_create = time;
		philo->process = process;
		philo->last_ate = time;
		philo->eat_count = 0;
		pthread_mutex_init(&philo->last_ate_mutex, NULL);
		pthread_mutex_init(&philo->eat_count_mutex, NULL);
	}
	while (process->current_philos < process->cur_num_of_philos
		&& process->current_philos < MAX_THREADS - 1)
	{
		philo = &process->philos[process->current_philos];
		if (pthread_create(&threads[process->current_philos],
				NULL, &philosopher_routine, philo) != 0)
			return (1);
		process->current_philos++;
	}
	return (0);
}

int	join_all_threads(t_process *process, pthread_t threads[],
		pthread_t monitor_thread, int thread_count)
{
	if (thread_count != process->cur_num_of_philos)
	{
		while (--thread_count >= 0)
			pthread_join(threads[thread_count], NULL);
		pthread_join(monitor_thread, NULL);
		return (1);
	}
	while (--thread_count >= 0)
		pthread_join(threads[thread_count], NULL);
	pthread_join(monitor_thread, NULL);
	return (0);
}

int	create_philosophers(t_process *process)
{
	pthread_t	threads[MAX_THREADS - 1];
	pthread_t	mt;
	long		time;
	int			i;

	process->current_philos = 0;
	process->philos = malloc(sizeof(t_philo) * process->cur_num_of_philos);
	if (!process->philos)
		return (1);
	time = get_time();
	if (create_philosopher_threads(process, threads, time) != 0)
	{
		i = process->current_philos;
		while (--i >= 0)
			pthread_join(threads[i], NULL);
		return (1);
	}
	if (pthread_create(&mt, NULL, &monitor_routine, process) != 0)
	{
		i = process->current_philos;
		while (--i >= 0)
			pthread_join(threads[i], NULL);
		return (1);
	}
	return (join_all_threads(process, threads, mt, process->current_philos));
}
