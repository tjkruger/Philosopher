/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:52:17 by tjkruger          #+#    #+#             */
/*   Updated: 2025/06/12 12:28:43 by tjkruger         ###   ########.fr       */
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
			ft_usleep(philo->id % 50);
		else
			ft_usleep(philo->id % 20);
	}
	if (philo->program->number_of_philosophers == 1)
	{
		print_action(philo, "is thinking", COLOR_CYAN);
		ft_usleep(philo->program->time_to_die);
		print_action(philo, "died", COLOR_RED);
		return (NULL);
	}
	pthread_mutex_init(&philo->last_eat_mutex, NULL);
	pthread_mutex_init(&philo->eat_count_mutex, NULL);
	if (philo->id % 2 == 0)
		ft_usleep(philo->program->time_to_eat);
	philo_loop(philo);
	pthread_mutex_destroy(&philo->last_eat_mutex);
	pthread_mutex_destroy(&philo->eat_count_mutex);
	return (NULL);
}
