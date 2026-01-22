/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:52:52 by tjkruger          #+#    #+#             */
/*   Updated: 2026/01/22 14:09:02 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int		wrong_input(char argc, char **argv)
{
	if (argc < 5 || argc > 6 || !is_really_a_number(argv))
	{
		printf("Usage: ./philo num_of_philoso time_to_die \
		time_to_eat time_to_sleep \
		[number_of_times_each_philosopher_must_eat\n"
			);
		return (1);
	}
	if (ft_atoi(argv[1]) > MAX_THREADS)
	{
		printf("NUmber of philos must be lower or equal to %d\n",
			MAX_THREADS);
		return (1);
	}
	return (0);
}

//lol comment
void	unlock_after_end(t_philo *philo)
{
	pthread_mutex_unlock(&philo->process->forks[philo->name]);
	if (philo->name == philo->process->number_of_philosophers - 1)
		pthread_mutex_unlock(&philo->process->forks[0]);
	else
		pthread_mutex_unlock(&philo->process->forks[philo->name + 1]);
}
