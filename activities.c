/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:52:34 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/26 18:16:30 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// end before the sleep if numberofmeal reach?

int	eating(t_philo *philo)
{
	if (check_deaths(philo) != 0)
		return (1);
	pthread_mutex_lock(philo->fork_right);
	pthread_mutex_lock(*(philo->fork_left));
	
	if (check_deaths(philo) != 0)
		return (pthread_mutex_unlock(philo->fork_right),
			pthread_mutex_unlock(*(philo->fork_left)), 1);
	printf("%lld %d has taken a fork\n", get_time(), philo->id);
	if (check_deaths(philo) != 0)
		return (pthread_mutex_unlock(philo->fork_right),
			pthread_mutex_unlock(*(philo->fork_left)), 1);
	printf("%lld %d is eating\n", get_time(), philo->id);
	philo->last_meal = get_time();
	usleep(philo->main->time_to_eat * 1000);
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(*(philo->fork_left));
	philo->nb_meals += 1;
	if (philo->nb_meals == philo->main->nb_of_eat)
		philo->main->finished_loop += 1;
	return (0);
}

int	sleeping(t_philo *philo, int time_to_sleep, int philo_no)
{
	if (check_deaths(philo) != 0)
		return (1);
	printf("%lld %d is sleeping\n", get_time(), philo_no);
	usleep(time_to_sleep * 1000);
	return (0);
}

int	thinking(t_philo *philo, int philo_no)
{
	if (check_deaths(philo) != 0)
		return (1);
	printf("%lld %d is thinking\n", get_time(), philo_no);
	return (0);
}
