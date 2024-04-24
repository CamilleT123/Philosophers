/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:57:12 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/24 13:19:26 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_fork
{
	FREE,
	BUSY,
}				t_fork;

// 1 philosopher
typedef struct s_main
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				check_nb_of_eat;
	int				nb_of_eat;
	int				*philo_no;
	long long int	start_time; // in microsecs
	pthread_mutex_t mutex;
}				t_main;

typedef struct s_philo
{
	int				id;
	int 			which_thread;
	long long int	last_meal; // in microsecs
	t_fork			fork_right;
	t_fork			fork_left;
	t_main			*main;
}				t_philo;

// thread.c
int				create_thread(t_main *main, t_philo *philo);
int				end_thread(t_main *main, t_philo *philo, pthread_t *th);

// routine.c
void			*routine(void *arg);
int				sleeping(t_main *main, int time_to_sleep, int philo_no);

// init.c
int				initialize_philo(t_main *main);
int				initialize_main(int ac, char **av, t_main *main);

// utils.c
long long int	get_time(void);

#endif