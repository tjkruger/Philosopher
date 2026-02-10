/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:52:35 by tjkruger          #+#    #+#             */
/*   Updated: 2026/02/10 17:11:33 by tjkruger         ###   ########.fr       */
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
	t_process	*prcs;
	long		current_time;

	prcs = (t_process *)args;
	while (prcs->dead == 0 && prcs->cur_num_of_philos > 1
		&& !check_all_satisfied(prcs))
	{
		i = -1;
		while (++i < prcs->current_philos && prcs->dead == 0)
		{
			last_meal = get_last_meal_time(&prcs->philos[i]);
			current_time = get_time();
			if (current_time - last_meal >= prcs->philos[i].process->die_time)
			{
				print_status(&prcs->philos[i], "died");
				set_simulation_over(prcs);
				return (NULL);
			}
		}
	}
	set_simulation_over(prcs);
	return (NULL);
}
