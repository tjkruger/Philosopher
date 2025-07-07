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

int	everyone_ate(t_program *program)
{
	int	i;
	int	eat_count;

	i = 0;
	if (program->must_eat_count == -1)
		return (0);
	while (i < program->current_philos)
	{
		pthread_mutex_lock(&program->philos[i].eat_count_mutex);
		eat_count = program->philos[i].eat_count;
		pthread_mutex_unlock(&program->philos[i].eat_count_mutex);
		if (eat_count < program->must_eat_count)
			return (0);
		i++;
	}
	return (1);
}

void	set_dead(t_program *program)
{
	pthread_mutex_lock(program->dead_mutex);
	program->dead = 1;
	pthread_mutex_unlock(program->dead_mutex);
}

int	do_be_dead(t_program *program)
{
	int	dead;

	pthread_mutex_lock(program->dead_mutex);
	dead = program->dead;
	pthread_mutex_unlock(program->dead_mutex);
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
	t_program	*program;
	long		time;

	program = (t_program *)args;
	while (program->dead == 0 && program->number_of_philosophers > 1
		&& !everyone_ate(program))
	{
		i = -1;
		while (++i < program->current_philos && program->dead == 0)
		{
			time = get_current_time();
			last_eat = get_last_eat(&program->philos[i]);
			if (time - last_eat
				>= program->philos[i].program->time_to_die)
			{
				print_action(&program->philos[i], "died");
				set_dead(program);
				return (NULL);
			}
		}
	}
	set_dead(program);
	return (NULL);
}
