/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:20:35 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/30 18:28:55 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_deaths(t_philo *philo)
{
	t_main	*main;

	main = philo->main;
	pthread_mutex_lock(&main->death);
	if (main->someone_died == 1)
		return (pthread_mutex_unlock(&main->death), 1);
	pthread_mutex_unlock(&main->death);
	if (main->finished_loops >= main->nb_philo)
		return (1);
	pthread_mutex_lock(&main->death);
	if (((timestamp(main) - philo->last_meal) >= main->time_to_die))
	{
		printf("%d %d died\n", timestamp(main), philo->id);
		main->someone_died = 1;
		return (pthread_mutex_unlock(&main->death), 1);
	}
	pthread_mutex_unlock(&main->death);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (check_deaths(philo) != 0)
		return (NULL);
	if (philo->id % 2)
	{
		if (thinking(philo, philo->id) != 0)
			return (NULL);
		usleep(philo->main->time_to_eat * 1000);
	}
	pthread_mutex_lock(&(philo->main->death));
	while (!philo->main->someone_died)
	{
		pthread_mutex_unlock(&(philo->main->death));
		if (eating(philo) != 0)
			return (NULL);
		if (sleeping(philo, philo->main->time_to_sleep, philo->id) != 0)
			return (NULL);
		if (thinking(philo, philo->id) != 0)
			return (NULL);
		pthread_mutex_lock(&(philo->main->death));
	}
	pthread_mutex_unlock(&(philo->main->death));
	return (NULL);
}

void	*routine_for_1(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&(philo->main->death));
	while (!philo->main->someone_died)
	{
		pthread_mutex_unlock(&(philo->main->death));
		if (thinking(philo, philo->id) != 0)
			return (NULL);
		usleep((philo->main->time_to_die + 5)  * 1000);
		pthread_mutex_lock(&(philo->main->death));
	}
	pthread_mutex_unlock(&(philo->main->death));
	return (NULL);
}

// int	eating(t_philo *philo)
// {

// 	if (pthread_mutex_lock(philo->fork_right) == 0)
// 	{
// 		if (check_deaths(philo) == 0)
// 			printf("%d %d has taken a fork\n", timestamp(philo->main), philo->id);
// 		else
// 			return (pthread_mutex_unlock(philo->fork_right), 1);
// 	}
// 	if (pthread_mutex_lock(*(philo->fork_left)) == 0)
// 	{
// 		if (check_deaths(philo) == 0)
// 			printf("%d %d has taken a fork\n", timestamp(philo->main), philo->id);
// 		else
// 			return (pthread_mutex_unlock(philo->fork_right),
// 				pthread_mutex_unlock(*(philo->fork_left)), 1);
// 	}
// 	if (check_deaths(philo) == 0)
// 	{
// 		printf("%d %d is eating\n",  timestamp(philo->main), philo->id);
// 		pthread_mutex_lock(&(philo->meal));
// 		philo->last_meal = timestamp(philo->main);
// 		philo->nb_meals += 1;
// 		pthread_mutex_unlock(&(philo->meal));
// 		usleep(philo->main->time_to_eat * 1000);
// 		pthread_mutex_unlock(philo->fork_right);
// 		pthread_mutex_unlock(*(philo->fork_left));
// 	}
// 	else
// 		return (pthread_mutex_unlock(philo->fork_right),
// 				pthread_mutex_unlock(*(philo->fork_left)), 1);
// 	if (philo->nb_meals == philo->main->target_nb_of_meals)
// 		philo->main->finished_loops += 1;
// 	return (0);
// }