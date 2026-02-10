/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:53:11 by tjkruger          #+#    #+#             */
/*   Updated: 2026/02/05 14:30:00 by tjkruger         ###   ########.fr       */
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
	int				philo_num;
	int				cur_num_of_philos;
	int				current_philos;
	int				dead;
	pthread_mutex_t	*printout_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*dead_mutex;
	t_philo			*philos;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				eat_count;
	int				must_eat_count;
}				t_process;

int		init_process(char **argv, t_process *process);
int		init_dead_mutex(t_process *process);
void	cleanup_process(t_process *process, int fork_count);
int		validate_input(char argc, char **argv);
int		validate_all_numbers(char **args);
int		create_philosophers(t_process *process);
int		create_philosopher_threads(t_process *process, pthread_t *threads,
			long time);
int		join_all_threads(t_process *process, pthread_t threads[],
			pthread_t monitor_thread, int thread_count);
void	*philosopher_routine(void *args);
void	philosopher_cycle(t_philo *philo);
void	philo_think_and_take_forks(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	take_left_fork(t_philo *philo);
void	take_right_fork(t_philo *philo);
void	release_both_forks(t_philo *philo);
void	*monitor_routine(void *args);
int		check_all_satisfied(t_process *process);
int		is_simulation_over(t_process *process);
void	set_simulation_over(t_process *process);
long	get_last_meal_time(t_philo *philo);
int		get_meal_count(t_philo *philo);
void	print_status(t_philo *philo, char *status);
int		ft_atoi(const char *nptr);
int		ft_strcmp(const char *s1, const char *s2);
long	get_current_time(void);
int		ft_usleep(int time_in_ms);
float	get_converted_time(long start);
int		is_number(const char *nptr);
long	get_time(void);

#endif