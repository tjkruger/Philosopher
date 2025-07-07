/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:52:28 by tjkruger          #+#    #+#             */
/*   Updated: 2025/07/07 13:47:10 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(philo->process->print_mutex);
	if (do_be_dead(philo->process) == 1)
	{
		pthread_mutex_unlock(philo->process->print_mutex);
		return ;
	}
	printf("%.0f %d %s\n",
		get_converted_time(philo->thread_create),
		philo->name + 1, action);
	pthread_mutex_unlock(philo->process->print_mutex);
}

void	left_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->process->forks[philo->name]);
	print_action(philo, "grabbed left fork");
}

void	right_fork(t_philo *philo)
{
	if (philo->name == philo->process->number_of_philosophers - 1)
		pthread_mutex_lock(&philo->process->forks[0]);
	else
		pthread_mutex_lock(&philo->process->forks[philo->name + 1]);
	print_action(philo, "grabbed right fork");
}

int	setup(char **argv, t_process *process)
{
	if (!process)
		return (1);
	process->number_of_philosophers = ft_atoi(argv[1]);
	process->time_to_die = ft_atoi(argv[2]);
	process->time_to_eat = ft_atoi(argv[3]);
	process->time_to_sleep = ft_atoi(argv[4]);
	process->dead = 0;
	process->forks = malloc(sizeof(pthread_mutex_t)
			* process->number_of_philosophers);
	if (!process->forks)
	{
		free(process);
		return (1);
	}
	process->print_mutex = malloc(sizeof(pthread_mutex_t));
	if (!process->print_mutex)
	{
		free(process->forks);
		free(process);
		return (1);
	}
	pthread_mutex_init(process->print_mutex, NULL);
	return (make_dead_mutex(process));
}

void	destroy(t_process *process, int i)
{
	while (--i >= 0)
		pthread_mutex_destroy(&process->forks[i]);
	pthread_mutex_destroy(process->print_mutex);
	free(process->forks);
	free(process->print_mutex);
	free(process->philos);
	free(process->dead_mutex);
	free(process);
}
