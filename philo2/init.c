/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:13:10 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/30 17:01:30 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	loop_initialize_philo(t_main *main, t_philo *philo)
{
	int		i;

	i = -1;
	while (++i < main->nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].nb_meals = 0;
		philo[i].last_meal = 0;
		philo[i].main = main;
		philo[i].fork_right = malloc(sizeof(pthread_mutex_t));
		if (!philo[i].fork_right)
			return (1);
		if (pthread_mutex_init(philo[i].fork_right, NULL) != 0)
			return (printf("mutex init failed"), 1);
		if (pthread_mutex_init(&(philo[i].meal), NULL) != 0)
			return (printf("mutex init failed"), 1);
		if (i == 0)
			philo[i].fork_left = &(philo[main->nb_philo - 1].fork_right);
		else
			philo[i].fork_left = &(philo[i - 1].fork_right);
	}
	return (0);
}

int	initialize_philo(t_main *main)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * main->nb_philo);
	if (!philo)
		return (1);
	if (loop_initialize_philo(main, philo) != 0)
		return (1);
	if (create_thread(main, philo) != 0)
		return (1);
	return (0);
}

int	initialize_main(int ac, char **av)
{
	t_main	*main;

	main = malloc(sizeof(t_main));
	main->nb_philo = atoi(av[1]);
	main->time_to_die = atoi(av[2]);
	main->time_to_eat = atoi(av[3]);
	main->time_to_sleep = atoi(av[4]);
	main->start_time = get_time();
	main->someone_died = 0;
	main->finished_loops = 0;
	if (ac == 6 && av[5])
	{
		main->check_nb_of_meals = 1;
		main->target_nb_of_meals = atoi(av[5]);
	}
	else
	{
		main->check_nb_of_meals = 0;
		main->target_nb_of_meals = 0;
	}
	if (pthread_mutex_init(&(main->death), NULL) != 0)
		return (printf("mutex init failed"), 1);
	if (initialize_philo(main) != 0)
		return (1);
	return (0);
}
