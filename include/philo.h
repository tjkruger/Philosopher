/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:53:11 by tjkruger          #+#    #+#             */
/*   Updated: 2025/06/09 13:53:11 by tjkruger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define MAX_THREADS 200
# define SECOND 1000000

typedef struct s_philo
{
	int					name;
	long				thread_create;
	int					eat_count;
	long				last_ate;
	pthread_mutex_t		eat_count_mutex;
	pthread_mutex_t		last_ate_mutex;
	struct s_process	*process;
}				t_philo;

typedef struct s_process
{
	int				number_of_philosophers;
	int				current_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				dead;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*dead_mutex;
	t_philo			*philos;
}				t_process;

void	*philosopher(void *args);
void	*monitor(void *args);

void	print_action(t_philo *philo, char *action);
void	left_fork(t_philo *philo);
void	right_fork(t_philo *philo);

void	destroy(t_process *process, int i);
int		setup(char **argv, t_process *process);
int		is_really_a_number(char **args);
int		wrong_input(char argc, char **argv);
int		make_dead_mutex(t_process *process);

void	unlock_after_end(t_philo *philo);

int		ft_atoi(const char *nptr);
long	get_current_time(void);
int		ft_usleep(int time_in_ms);
float	get_converted_time(long start);
int		is_number(const char *nptr);
int		do_be_dead(t_process *process);

void	think_while_grabbing_fork(t_philo *philo);
void	eating(t_philo *philo);
void	sleep_philo(t_philo *philo);
int		spawn_philo_fr(t_process *process, pthread_t *threads, long time);

#endif