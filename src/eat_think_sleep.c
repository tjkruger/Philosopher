/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_think_sleep.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:26:42 by tjkruger          #+#    #+#             */
/*   Updated: 2025/07/07 13:22:03 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	eat_and_whash_dishes(t_philo *philo)
{
	print_action(philo, "is eating");
	ft_usleep(philo->program->time_to_eat);
	pthread_mutex_unlock(&philo->program->forks[philo->name]);
	if (philo->name == philo->program->number_of_philosophers - 1)
		pthread_mutex_unlock(&philo->program->forks[0]);
	else
		pthread_mutex_unlock(&philo->program->forks[philo->name + 1]);
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
	ft_usleep(philo->program->time_to_sleep);
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

int	spawn_philo_fr(t_program *program, pthread_t *threads, long time)
{
	while (program->current_philos < program->number_of_philosophers
		&& program->current_philos < PTHREAD_THREADS_MAX - 1)
	{
		setup_philo_struct(&program->philos[program->current_philos],
			time, program);
		if (pthread_create(&threads[program->current_philos],
				NULL, &philosopher,
				&program->philos[program->current_philos]) != 0)
			return (1);
		program->current_philos++;
	}
	return (0);
}