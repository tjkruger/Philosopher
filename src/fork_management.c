/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:52:28 by tjkruger          #+#    #+#             */
/*   Updated: 2026/02/05 14:30:00 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	take_left_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->process->forks[philo->name]);
	print_status(philo, "has taken a fork");
}

void	take_right_fork(t_philo *philo)
{
	if (philo->name == philo->process->cur_num_of_philos - 1)
		pthread_mutex_lock(&philo->process->forks[0]);
	else
		pthread_mutex_lock(&philo->process->forks[philo->name + 1]);
	print_status(philo, "has taken a fork");
}

void	release_both_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->process->forks[philo->name]);
	if (philo->name == philo->process->cur_num_of_philos - 1)
		pthread_mutex_unlock(&philo->process->forks[0]);
	else
		pthread_mutex_unlock(&philo->process->forks[philo->name + 1]);
}
