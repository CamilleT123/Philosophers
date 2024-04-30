/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:12:27 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/30 16:24:43 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	loop_initialize_philo(t_main *main, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < main->nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].last_meal = main->start_time;
		philo[i].nb_meals = 0;
		philo[i].main = main;
		philo[i].fork_right = malloc(sizeof(pthread_mutex_t));
		if (!philo[i].fork_right)
			return (1);
		if (pthread_mutex_init(philo[i].fork_right, NULL) != 0)
			return (printf("mutex init failed"), 1);
		if (pthread_mutex_init(&(philo[i].meal), NULL) != 0)
			return (printf("mutex init failed"), 1);
		// philo[i].R_is_locked = malloc(sizeof(bool));
		// philo[i].R_is_locked = false;
		// printf("Risunlocked=%d\n", philo[i].R_is_locked);
		if (i == 0)
			philo[i].fork_left = &philo[main->nb_philo - 1].fork_right;
		else
			philo[i].fork_left = &philo[i - 1].fork_right;
		// printf("Lislocked=%d\n", *(philo[i].L_is_locked));
	}
	// i = -1;
	// while (++i < main->nb_philo)
	// {
	// 	if (i == 0)
	// 		philo[i].L_is_locked = &philo[main->nb_philo - 1].R_is_locked;
	// 	else
	// 		philo[i].L_is_locked = &philo[i - 1].R_is_locked;
	// }
	// philo[3].R_is_locked = true;
	// *(philo[3].L_is_locked) = true;
	// printf("2Risunlocked=%d\n", philo[2].R_is_locked);
	// printf("4Lisunlocked=%d\n", *(philo[4].L_is_locked));
	return (0);
}

// int	initialize_philos(t_main *main, t_philo **philos, t_philo *philo)
// {
// 	int		i;

// 	i = -1;
// 	philos = malloc(sizeof(t_philo *) * main->nb_philo);
// 	if (!philos)
// 		return (1);
// 	i = -1;
// 	while (++i < main->nb_philo)
// 	{
// 		philos[i] = &philo[i];
// 	}
// 	return (0);
// }

int	initialize_philo(t_main *main)
{
	t_philo	*philo;
	t_philo	**philos;

	philos = NULL;
	philo = malloc(sizeof(t_philo) * main->nb_philo + 1);
	if (!philo)
		return (1);
	if (loop_initialize_philo(main, philo) != 0)
		return (1);
	// initialize_philos(main, philos, philo);
	if (create_thread(main, philo) != 0)
		return (1);
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
	main->someone_died = 0;
	main->finished_loop = 0;
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
	if (pthread_mutex_init(&(main->death), NULL) != 0)
		return (printf("mutex init failed"), 1);
	return (0);
}
