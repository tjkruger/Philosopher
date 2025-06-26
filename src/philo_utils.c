/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:52:28 by tjkruger          #+#    #+#             */
/*   Updated: 2025/06/12 12:13:50 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_action(t_philo *philo, char *action, char *color)
{
	pthread_mutex_lock(philo->program->print_mutex);
	if (do_be_dead(philo->program) == 1)
	{
		pthread_mutex_unlock(philo->program->print_mutex);
		return ;
	}
	printf("%s%.0f %d %s%s\n", color,
		get_converted_time(philo->thread_create),
		philo->id + 1, action, COLOR_RESET);
	pthread_mutex_unlock(philo->program->print_mutex);
}

void	left_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->forks[philo->id]);
	print_action(philo, "is armed now", COLOR_GREEN);
}

void	right_fork(t_philo *philo)
{
	if (philo->id == philo->program->number_of_philosophers - 1)
		pthread_mutex_lock(&philo->program->forks[0]);
	else
		pthread_mutex_lock(&philo->program->forks[philo->id + 1]);
	print_action(philo, "is armed now", COLOR_GREEN);
}

int	setup(char **argv, t_program *program)
{
	if (!program)
		return (1);
	program->number_of_philosophers = ft_atoi(argv[1]);
	program->time_to_die = ft_atoi(argv[2]);
	program->time_to_eat = ft_atoi(argv[3]);
	program->time_to_sleep = ft_atoi(argv[4]);
	program->dead = 0;
	program->forks = malloc(sizeof(pthread_mutex_t)
			* program->number_of_philosophers);
	if (!program->forks)
	{
		free(program);
		return (1);
	}
	program->print_mutex = malloc(sizeof(pthread_mutex_t));
	if (!program->print_mutex)
	{
		free(program->forks);
		free(program);
		return (1);
	}
	pthread_mutex_init(program->print_mutex, NULL);
	return (make_dead_mutex(program));
}

void	destroy(t_program *program, int i)
{
	while (--i >= 0)
		pthread_mutex_destroy(&program->forks[i]);
	pthread_mutex_destroy(program->print_mutex);
	free(program->forks);
	free(program->print_mutex);
	free(program->philos);
	free(program->dead_mutex);
	free(program);
}
