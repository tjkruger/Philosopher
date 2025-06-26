/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_think_sleep.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:26:42 by tjkruger          #+#    #+#             */
/*   Updated: 2025/06/12 12:28:51 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	eat_and_whash_dishes(t_philo *philo)
{
	print_action(philo, "is eating", COLOR_MAGENTA);
	ft_usleep(philo->program->time_to_eat);
	pthread_mutex_unlock(&philo->program->forks[philo->id]);
	if (philo->id == philo->program->number_of_philosophers - 1)
		pthread_mutex_unlock(&philo->program->forks[0]);
	else
		pthread_mutex_unlock(&philo->program->forks[philo->id + 1]);
	pthread_mutex_lock(&philo->last_eat_mutex);
	philo->last_eat = get_current_time();
	pthread_mutex_unlock(&philo->last_eat_mutex);
	pthread_mutex_lock(&philo->eat_count_mutex);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->eat_count_mutex);
}

void	sleep_philo(t_philo *philo)
{
	print_action(philo, "is sleeping", COLOR_YELLOW);
	ft_usleep(philo->program->time_to_sleep);
}

void	think_while_grabbing_fork(t_philo *philo)
{
	print_action(philo, "is thinking", COLOR_CYAN);
	if (philo->id % 2 == 0)
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
