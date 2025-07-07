/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_think_sleep.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:26:42 by tjkruger          #+#    #+#             */
/*   Updated: 2025/07/07 13:59:09 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	eat_and_whash_dishes(t_philo *philo)
{
	print_action(philo, "is eating");
	ft_usleep(philo->process->time_to_eat);
	pthread_mutex_unlock(&philo->process->forks[philo->name]);
	if (philo->name == philo->process->number_of_philosophers - 1)
		pthread_mutex_unlock(&philo->process->forks[0]);
	else
		pthread_mutex_unlock(&philo->process->forks[philo->name + 1]);
	pthread_mutex_lock(&philo->last_ate_mutex);
	philo->last_ate = get_current_time();
	pthread_mutex_unlock(&philo->last_ate_mutex);
	pthread_mutex_lock(&philo->eat_count_mutex);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->eat_count_mutex);
}

void	sleep_philo(t_philo *philo)
{
	print_action(philo, "is sleeping");
	ft_usleep(philo->process->time_to_sleep);
}

void	think_while_grabbing_fork(t_philo *philo)
{
	print_action(philo, "is thinking");
	if (philo->name % 2 != 0)
	{
		left_fork(philo);
		right_fork(philo);
	}
	else
	{
		right_fork(philo);
		left_fork(philo);
	}
}

int	spawn_philo_fr(t_process *process, pthread_t *threads, long time)
{
	while (process->current_philos < process->number_of_philosophers
		&& process->current_philos < MAX_THREADS - 1)
	{
		t_philo *philo = &process->philos[process->current_philos];

		philo->name = process->current_philos;
		philo->thread_create = time;
		philo->process = process;
		philo->last_ate = time;
		philo->eat_count = 0;

		if (pthread_create(&threads[process->current_philos],
				NULL, &philosopher, philo) != 0)
			return (1);

		process->current_philos++;
	}
	return (0);
}
