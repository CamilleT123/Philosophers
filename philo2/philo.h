/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:59:33 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/30 17:55:41 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				nb_meals;
	int				last_meal;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	**fork_left;
	pthread_mutex_t	meal;
	struct s_main	*main;
}					t_philo;

typedef struct s_main
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				check_nb_of_meals;
	int				target_nb_of_meals;
	int				someone_died;
	int				finished_loops;
	long long int	start_time;
	pthread_mutex_t	death;
}					t_main;

// init.c
int				initialize_main(int ac, char **av);

// threads.c
int				create_thread(t_main *main, t_philo *philo);

// routine.c
void			*routine(void *arg);
int				check_deaths(t_philo *philo);
void			*routine_for_1(void *arg);

// activities.c
int				thinking(t_philo *philo, int philo_no);
int				eating(t_philo *philo);
int				sleeping(t_philo *philo, int time_to_sleep, int philo_no);

// utils.c
long long int	get_time(void);
int				timestamp(t_main *main);

#endif