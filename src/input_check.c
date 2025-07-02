/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:52:52 by tjkruger          #+#    #+#             */
/*   Updated: 2025/07/02 11:27:21 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	input_invalid(char argc, char **argv)
{
	if (argc < 5 || argc > 6 || !is_all_numbers(argv))
	{
		printf("%sUsage: ./philo number_of_philosophers time_to_die \
		time_to_eat time_to_sleep  \
		[number_of_times_each_philosopher_must_eat%s\n",
			COLOR_RED, COLOR_RESET);
		return (1);
	}
	if (ft_atoi(argv[1]) > PTHREAD_THREADS_MAX)
	{
		printf("%sThere must be less then or equal %d philos%s\n",
			COLOR_RED, PTHREAD_THREADS_MAX, COLOR_RESET);
		return (1);
	}
	return (0);
}

void	unlock_after_end(t_philo *philo)
{
	pthread_mutex_unlock(&philo->program->forks[philo->name]);
	if (philo->name == philo->program->number_of_philosophers - 1)
		pthread_mutex_unlock(&philo->program->forks[0]);
	else
		pthread_mutex_unlock(&philo->program->forks[philo->name + 1]);
}
