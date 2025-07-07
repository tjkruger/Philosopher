/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:52:42 by tjkruger          #+#    #+#             */
/*   Updated: 2025/06/09 13:52:42 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>

int	is_really_a_number(char **args)
{
	int	i;

	i = 0;
	while (args[++i])
	{
		if (!is_number(args[i]))
			return (0);
	}
	return (1);
}

int	join_threads(t_process *process, pthread_t threads[],
	pthread_t monitor_thread, int number_of_threads)
{
	if (number_of_threads != process->number_of_philosophers)
	{
		while (--number_of_threads >= 0)
			pthread_join(threads[number_of_threads], NULL);
		pthread_join(monitor_thread, NULL);
		return (1);
	}
	while (--number_of_threads >= 0)
		pthread_join(threads[number_of_threads], NULL);
	pthread_join(monitor_thread, NULL);
	return (0);
}

int	spawn_philos(t_process *process)
{
	pthread_t	threads[MAX_THREADS - 1];
	pthread_t	monitor_thread;
	long		time;

	process->current_philos = 0;
	process->philos = malloc(sizeof(t_philo) * process->number_of_philosophers);
	if (!process->philos)
		return (1);
	time = get_current_time();
	if (spawn_philo_fr(process, threads, time) != 0)
		return (1);
	pthread_create(&monitor_thread, NULL, &monitor, process);
	return (join_threads(process, threads, monitor_thread,
			process->current_philos));
}

int	main(int argc, char **argv)
{
	t_process	*process;
	int			i;
	int			return_value;

	i = -1;
	if (wrong_input(argc, argv))
		return (1);
	process = malloc(sizeof(t_process));
	if (setup(argv, process))
		return (1);
	while (++i < process->number_of_philosophers)
		pthread_mutex_init(&process->forks[i], NULL);
	if (argc == 6)
		process->must_eat_count = ft_atoi(argv[5]);
	else
		process->must_eat_count = -1;
	return_value = spawn_philos(process);
	destroy(process, i);
	return (return_value);
}
