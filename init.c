/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:12:27 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/24 13:20:49 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	initialize_philo(t_main *main)
{
	int		i;
	t_philo	*philo;
	// t_fork	*fork;
	
	i = -1;
	philo = malloc(sizeof(t_philo) * main->nb_philo);
	// fork = malloc(sizeof(t_fork) * main->nb_philo);
	if (!philo)
		return (1);
	// while (++i < main->nb_philo)
	// 	fork[i] = FREE;
	// i = -1;
	while (++i < main->nb_philo)
	{
		printf("i=%d\n", i);
		philo[i].id = i;
		philo[i].which_thread = 0;
		philo[i].last_meal = main->start_time;
		philo[i].fork_right = FREE;
		if (i == 0)
			philo[i].fork_left = philo[main->nb_philo - 1].fork_right;
		else
			philo[i].fork_left = philo[i - 1].fork_right;
		philo[i].main = main;
	}
	create_thread(main, philo);
	return (0);
}

int	initialize_main(int ac, char **av, t_main *main)
{
	main->nb_philo = atoi(av[1]);
	main->time_to_die = atoi(av[2]);
	main->time_to_eat = atoi(av[3]);
	main->time_to_sleep = atoi(av[4]);
	main->check_nb_of_eat = 0;
	main->start_time = get_time();
	if (ac == 6 && av[5])
	{
		main->check_nb_of_eat = 1;
		main->nb_of_eat = atoi(av[5]);
	}
	else
	{
		main->check_nb_of_eat = 0;
		main->nb_of_eat = 0;
	}
	// printf("1. start_time= %lld\n", main->start_time); // in microsecs
	// printf("time_to_die= %d\n", main->time_to_die);
	// printf("time_to_eat= %d\n", main->time_to_eat);
	// printf("time_to_sleep= %d\n", main->time_to_sleep);
	// printf("nb_eat= %d\n", main->nb_of_eat);
	return (0);
}
