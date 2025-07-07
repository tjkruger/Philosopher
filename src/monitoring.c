/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:52:35 by tjkruger          #+#    #+#             */
/*   Updated: 2025/06/09 13:52:35 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	everyone_ate(t_process *process)
{
	int	i;
	int	eat_count;

	i = 0;
	if (process->must_eat_count == -1)
		return (0);
	while (i < process->current_philos)
	{
		pthread_mutex_lock(&process->philos[i].eat_count_mutex);
		eat_count = process->philos[i].eat_count;
		pthread_mutex_unlock(&process->philos[i].eat_count_mutex);
		if (eat_count < process->must_eat_count)
			return (0);
		i++;
	}
	return (1);
}

void	set_dead(t_process *process)
{
	pthread_mutex_lock(process->dead_mutex);
	process->dead = 1;
	pthread_mutex_unlock(process->dead_mutex);
}

int	do_be_dead(t_process *process)
{
	int	dead;

	pthread_mutex_lock(process->dead_mutex);
	dead = process->dead;
	pthread_mutex_unlock(process->dead_mutex);
	return (dead);
}

long	get_last_eat(t_philo *philo)
{
	long	last_eat;

	pthread_mutex_lock(&philo->last_ate_mutex);
	last_eat = philo->last_ate;
	pthread_mutex_unlock(&philo->last_ate_mutex);
	return (last_eat);
}

void	*monitor(void *args)
{
	int			i;
	long		last_eat;
	t_process	*process;
	long		time;

	process = (t_process *)args;
	while (process->dead == 0 && process->number_of_philosophers > 1
		&& !everyone_ate(process))
	{
		i = -1;
		while (++i < process->current_philos && process->dead == 0)
		{
			time = get_current_time();
			last_eat = get_last_eat(&process->philos[i]);
			if (time - last_eat
				>= process->philos[i].process->time_to_die)
			{
				print_action(&process->philos[i], "died");
				set_dead(process);
				return (NULL);
			}
		}
	}
	set_dead(process);
	return (NULL);
}
