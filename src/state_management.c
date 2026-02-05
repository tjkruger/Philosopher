/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:52:35 by tjkruger          #+#    #+#             */
/*   Updated: 2026/02/05 14:30:00 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	set_simulation_over(t_process *process)
{
	pthread_mutex_lock(process->dead_mutex);
	process->dead = 1;
	pthread_mutex_unlock(process->dead_mutex);
}

int	is_simulation_over(t_process *process)
{
	int	dead;

	pthread_mutex_lock(process->dead_mutex);
	dead = process->dead;
	pthread_mutex_unlock(process->dead_mutex);
	return (dead);
}

long	get_last_meal_time(t_philo *philo)
{
	long	last_meal;

	pthread_mutex_lock(&philo->last_ate_mutex);
	last_meal = philo->last_ate;
	pthread_mutex_unlock(&philo->last_ate_mutex);
	return (last_meal);
}

int	get_meal_count(t_philo *philo)
{
	int	count;

	pthread_mutex_lock(&philo->eat_count_mutex);
	count = philo->eat_count;
	pthread_mutex_unlock(&philo->eat_count_mutex);
	return (count);
}
