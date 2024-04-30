/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:57:12 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/30 14:59:03 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
#include <stdbool.h>

typedef struct s_main
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				check_nb_of_eat;
	int				nb_of_eat;
	// t_philo			*philo;
	int				someone_died;
	int				finished_loop;
	long long int	start_time;
	pthread_mutex_t	death;
}					t_main;

typedef struct s_philo
{
	int				id;
	int				nb_meals;
	long long int	last_meal;
	t_main			*main;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	**fork_left;
	pthread_mutex_t	meal;
}					t_philo;

// typedef struct s_philos
// {
// 	t_philo **philo;
// }					t_philos;


// init.c
int					initialize_philo(t_main *main);
int					initialize_main(int ac, char **av, t_main *main);

// thread.c
// int					create_thread(t_main *main, t_philo *philo, t_philo **philos);
int					create_thread(t_main *main, t_philo *philo);
int					end_thread(t_main *main, t_philo *philo, pthread_t *th);

// routine.c
void				*routine_for_1(void *arg);
void				*routine(void *arg);
int					check_deaths(t_philo *philo);
// void	*monitoring(void *arg);

// activities.c
int					sleeping(t_philo *philo, int time_to_sleep, int philo_no);
int					eating(t_philo *philo);
int					thinking(t_philo *philo, int philo_no);

// utils.c
long long int		get_time(void);

#endif