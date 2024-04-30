/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:46:10 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/30 18:29:48 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thinking(t_philo *philo, int philo_no)
{
	if (check_deaths(philo) != 0)
		return (1);
	(void) philo;
	printf("%d %d is thinking\n", timestamp(philo->main), philo_no);
	return (0);
}

int	sleeping(t_philo *philo, int time_to_sleep, int philo_no)
{
	if (check_deaths(philo) != 0)
		return (1);
	(void) philo;
	printf("%d %d is sleeping\n", timestamp(philo->main), philo_no);
	usleep(time_to_sleep * 1000);
	return (0);
}

// static int	taking_fork(t_philo *philo, pthread_mutex_t *mutex, char *message)
// {
// 	if (pthread_mutex_lock(mutex) == 0)
// 	{
// 		if (check_deaths(philo) == 0)
// 			printf("%d %d %s\n", timestamp(philo->main), philo->id, message);
// 		else
// 			return (pthread_mutex_unlock(mutex), 1);
// 	}
// 	return (0);
// }

// int	eating(t_philo *philo)
// {
// 	if (taking_fork(philo, philo->fork_right, "has taken a fork") != 0)
// 		return (1);
// 	if (taking_fork(philo, *(philo->fork_left), "has taken a fork") != 0)
// 		return (pthread_mutex_unlock(philo->fork_right), 1);
// 	if (check_deaths(philo) == 0)
// 	{
// 		printf("%d %d is eating\n", timestamp(philo->main), philo->id);
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
// 			pthread_mutex_unlock(*(philo->fork_left)), 1);
// 	if (philo->nb_meals == philo->main->target_nb_of_meals)
// 		philo->main->finished_loops += 1;
// 	return (0);
// }

int	eating(t_philo *philo)
{
	if (check_deaths(philo) != 0)
		return (1);
	pthread_mutex_lock(philo->fork_right);
	printf("%d %d has taken a fork\n", timestamp(philo->main), philo->id);
	if (check_deaths(philo) != 0)
		return (pthread_mutex_unlock(philo->fork_right), 1);
	pthread_mutex_lock(*(philo->fork_left));
	printf("%d %d has taken a fork\n", timestamp(philo->main), philo->id);
	if (check_deaths(philo) != 0)
		return (pthread_mutex_unlock(philo->fork_right),
			pthread_mutex_unlock(*(philo->fork_left)), 1);
	printf("%d %d is eating\n", timestamp(philo->main), philo->id);
	pthread_mutex_lock(&(philo->meal));
	philo->last_meal = timestamp(philo->main);
	philo->nb_meals += 1;
	pthread_mutex_unlock(&(philo->meal));
	usleep(philo->main->time_to_eat * 1000);
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(*(philo->fork_left));
	pthread_mutex_lock(&(philo->meal));
	if (philo->nb_meals == philo->main->target_nb_of_meals)
		philo->main->finished_loops += 1;
	pthread_mutex_unlock(&(philo->meal));
	return (0);
}
