/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:52:17 by tjkruger          #+#    #+#             */
/*   Updated: 2025/07/07 13:31:57 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void	philo_loop(t_philo *philo)
{
	while (do_be_dead(philo->program) == 0)
	{
		think_while_grabbing_fork(philo);
		if (do_be_dead(philo->program) == 1)
			break ;
		eat_and_whash_dishes(philo);
		if (do_be_dead(philo->program) == 1)
			break ;
		if (philo->program->must_eat_count != -1
			&& philo->eat_count >= philo->program->must_eat_count)
			break ;
		sleep_philo(philo);
	}
}

void	*philosopher(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->program->number_of_philosophers % 2 == 1)
	{
		if (philo->program->number_of_philosophers >= 100)
			ft_usleep(philo->name % 50);
		else
			ft_usleep(philo->name % 20);
	}
	if (philo->program->number_of_philosophers == 1)
	{
		print_action(philo, "is thinking");
		ft_usleep(philo->program->time_to_die);
		print_action(philo, "died");
		return (NULL);
	}
	pthread_mutex_init(&philo->last_ate_mutex, NULL);
	pthread_mutex_init(&philo->eat_count_mutex, NULL);
	if (philo->name % 2 == 0)
		ft_usleep(philo->program->time_to_eat);
	philo_loop(philo);
	pthread_mutex_destroy(&philo->last_ate_mutex);
	pthread_mutex_destroy(&philo->eat_count_mutex);
	return (NULL);
}
