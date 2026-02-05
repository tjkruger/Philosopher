/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:52:52 by tjkruger          #+#    #+#             */
/*   Updated: 2026/02/05 14:30:00 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	validate_all_numbers(char **args)
{
	int	i;

	i = 0;
	while (args[++i])
	{
		if (!is_number(args[i]))
			return (0);
	}
	return (1);
}

int	validate_input(char argc, char **argv)
{
	if (argc < 5 || argc > 6 || !validate_all_numbers(argv))
	{
		printf("Usage: ./philo <num_of_philos> <time_to_die> ");
		printf("<time_to_eat> <time_to_sleep> [times_must_eat]\n");
		return (1);
	}
	if (ft_atoi(argv[1]) > MAX_THREADS)
	{
		printf("Number of philos must be lower or equal to %d\n",
			MAX_THREADS);
		return (1);
	}
	return (0);
}
