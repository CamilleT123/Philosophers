/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:52:34 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/30 15:59:28 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// end before the sleep if numberofmeal reach?

int	eating(t_philo *philo)
{
	if (check_deaths(philo) != 0)
		return (1);
	// printf("%d, is here\n", philo->id);
	// printf("%d, Rislocked=%d\n", philo->id, philo->R_is_locked);
	// printf("%d, Lislocked=%d\n", philo->id, *(philo->L_is_locked));
	// if (philo->R_is_locked == true)
	// {
	// 	printf("%d, fork R not available\n", philo->id);
	// 	usleep(1000);
	// }
	// if (*(philo->L_is_locked) == true)
	// {
	// 	printf("%d, fork L not available\n", philo->id);
	// 	usleep(1000);
	// }
	pthread_mutex_lock(philo->fork_right);
	// philo->R_is_locked = true;
	// printf("%d, R locked=%d\n", philo->id, philo->R_is_locked);
	pthread_mutex_lock(*(philo->fork_left));
	// *(philo->L_is_locked) = true;
	// printf("%d, L locked=%d\n", philo->id, *(philo->L_is_locked));
	if (check_deaths(philo) != 0)
		return (pthread_mutex_unlock(philo->fork_right),
			pthread_mutex_unlock(*(philo->fork_left)), 1);
	printf("%lld %d has taken a fork\n", get_time(), philo->id);
	if (check_deaths(philo) != 0)
		return (pthread_mutex_unlock(philo->fork_right),
			pthread_mutex_unlock(*(philo->fork_left)), 1);
	printf("%lld %d is eating\n", (philo->main->start_time - get_time()), philo->id);
	pthread_mutex_lock(&(philo->meal));
	philo->last_meal = get_time();
	printf("%d last meal = %lld\n", philo->id, philo->last_meal);
	pthread_mutex_unlock(&(philo->meal));
	// printf("%d last meal add = %p\n", philo->id, &(philo->last_meal));
	// printf("%d philo add = %p\n", philo->id, &(philo));
	usleep(philo->main->time_to_eat * 1000);
	// philo->R_is_locked = false;
	// printf("Runlocked=%d\n", philo->R_is_locked);
	// *(philo->L_is_locked) = false;
	// printf("Lunlocked=%d\n", *(philo->L_is_locked));
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
