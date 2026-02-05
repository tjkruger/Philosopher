/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:52:28 by tjkruger          #+#    #+#             */
/*   Updated: 2026/02/05 14:30:00 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(philo->process->printout_mutex);
	if (is_simulation_over(philo->process) == 1
		&& ft_strcmp(status, "died") != 0)
	{
		pthread_mutex_unlock(philo->process->printout_mutex);
		return ;
	}
	printf("%.0f %d %s\n",
		get_converted_time(philo->thread_create),
		philo->name + 1, status);
	pthread_mutex_unlock(philo->process->printout_mutex);
}
