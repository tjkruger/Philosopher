/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:26:42 by tjkruger          #+#    #+#             */
/*   Updated: 2026/02/10 16:48:03 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_think_and_take_forks(t_philo *philo)
{
	print_status(philo, "is thinking");
	if (philo->process->philo_num % 2)
		ft_usleep(philo->process->die_time / 2);

	if (philo->name % 2 != 0)
	{
		take_left_fork(philo);
		take_right_fork(philo);
	}
	else
	{
		take_left_fork(philo);
		take_right_fork(philo);
	}
}

void philo_eat(t_philo *philo)
{
    print_status(philo, "is eating");
    ft_usleep(philo->process->eat_time);
    pthread_mutex_lock(&philo->last_ate_mutex);
    philo->last_ate = get_time();
    pthread_mutex_unlock(&philo->last_ate_mutex);
    pthread_mutex_unlock(&philo->process->forks[philo->name]);
    if (philo->name == philo->process->cur_num_of_philos - 1)
        pthread_mutex_unlock(&philo->process->forks[0]);
    else
        pthread_mutex_unlock(&philo->process->forks[philo->name + 1]);
    pthread_mutex_lock(&philo->eat_count_mutex);
    philo->eat_count++;
    pthread_mutex_unlock(&philo->eat_count_mutex);
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->process->sleep_time);
}
