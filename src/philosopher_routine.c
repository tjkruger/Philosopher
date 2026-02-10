/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:52:17 by tjkruger          #+#    #+#             */
/*   Updated: 2026/02/10 17:12:29 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philosopher_cycle(t_philo *philo)
{
	while (is_simulation_over(philo->process) == 0)
	{
		philo_think_and_take_forks(philo);
		if (is_simulation_over(philo->process) == 1)
		{
			release_both_forks(philo);
			break ;
		}
		philo_eat(philo);
		if (is_simulation_over(philo->process) == 1)
			break ;
		if (philo->process->must_eat_count != -1
			&& philo->eat_count >= philo->process->must_eat_count)
			break ;
		philo_sleep(philo);
	}
}

void	*philosopher_routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->process->cur_num_of_philos % 2 == 1)
	{
		if (philo->process->cur_num_of_philos >= 100)
			usleep(philo->name % 50);
		else
			usleep(philo->name % 20);
	}
	if (philo->process->cur_num_of_philos == 1)
	{
		print_status(philo, "is thinking");
		ft_usleep(philo->process->die_time);
		print_status(philo, "died");
		return (NULL);
	}
	if (philo->name % 2 == 0)
		ft_usleep(philo->process->eat_time / 2);
	philosopher_cycle(philo);
	return (NULL);
}
