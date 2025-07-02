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

int	is_all_numbers(char **args)
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

int	join_threads(t_program *program, pthread_t threads[],
	pthread_t monitor_thread, int amount)
{
	if (amount != program->number_of_philosophers)
	{
		while (--amount >= 0)
			pthread_join(threads[amount], NULL);
		pthread_join(monitor_thread, NULL);
		return (1);
	}
	while (--amount >= 0)
		pthread_join(threads[amount], NULL);
	pthread_join(monitor_thread, NULL);
	return (0);
}

void	setup_philo_struct(t_philo *philo, long time, t_program *program)
{
	philo->name = program->current_philos;
	philo->thread_create = time;
	philo->program = program;
	philo->last_ate = time;
	philo->eat_count = 0;
}



int	spawn_philos(t_program *program)
{
	pthread_t	threads[PTHREAD_THREADS_MAX - 1];
	pthread_t	monitor_thread;
	long		time;

	program->current_philos = 0;
	program->philos = malloc(sizeof(t_philo) * program->number_of_philosophers);
	if (!program->philos)
		return (1);
	time = get_current_time();
	if (spawn_philo_fr(program, threads, time) != 0)
		return (1);
	pthread_create(&monitor_thread, NULL, &monitor, program);
	return (join_threads(program, threads, monitor_thread,
			program->current_philos));
}

int	main(int argc, char **argv)
{
	t_program	*program;
	int			i;
	int			return_value;

	i = -1;
	if (input_invalid(argc, argv))
		return (1);
	program = malloc(sizeof(t_program));
	if (setup(argv, program))
		return (1);
	while (++i < program->number_of_philosophers)
		pthread_mutex_init(&program->forks[i], NULL);
	if (argc == 6)
		program->must_eat_count = ft_atoi(argv[5]);
	else
		program->must_eat_count = -1;
	return_value = spawn_philos(program);
	destroy(program, i);
	return (return_value);
}
