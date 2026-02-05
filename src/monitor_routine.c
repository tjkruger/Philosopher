/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:52:35 by tjkruger          #+#    #+#             */
/*   Updated: 2026/02/05 14:30:00 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_all_satisfied(t_process *process)
{
	int	i;
	int	current_eat_count;

	i = 0;
	if (process->must_eat_count == -1)
		return (0);
	while (i < process->current_philos)
	{
		pthread_mutex_lock(&process->philos[i].eat_count_mutex);
		current_eat_count = process->philos[i].eat_count;
		pthread_mutex_unlock(&process->philos[i].eat_count_mutex);
		if (current_eat_count < process->must_eat_count)
			return (0);
		i++;
	}
	return (1);
}

void	*monitor_routine(void *args)
{
	int			i;
	long		last_meal;
	t_process	*process;
	long		current_time;

	process = (t_process *)args;
	while (process->dead == 0 && process->cur_num_of_philos > 1
		&& !check_all_satisfied(process))
	{
		i = -1;
		while (++i < process->current_philos && process->dead == 0)
		{
			current_time = get_time();
			last_meal = get_last_meal_time(&process->philos[i]);
			if (current_time - last_meal >= process->philos[i].process->die_time)
			{
				print_status(&process->philos[i], "died");
				set_simulation_over(process);
				return (NULL);
			}
		}
	}
	set_simulation_over(process);
	return (NULL);
}
