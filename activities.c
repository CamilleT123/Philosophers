/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:46:10 by ctruchot          #+#    #+#             */
/*   Updated: 2024/05/06 15:52:02 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thinking(t_philo *philo, int philo_no)
{
	int	time_to_sleep;

	time_to_sleep = philo->main->time_to_sleep;
	if (check_deaths(philo) != 0)
		return (1);
	pthread_mutex_lock(&(philo->main->print));
	printf("%d %d is thinking\n", timestamp(philo->main), philo_no);
	pthread_mutex_unlock(&(philo->main->print));
	if (philo->main->time_to_sleep <= philo->main->time_to_eat)
		if (ft_sleep(philo, (philo->main->time_to_eat - time_to_sleep
					+ 2)) != 0)
			return (1);
	return (0);
}

int	sleeping(t_philo *philo, int time_to_sleep, int philo_no)
{
	if (check_deaths(philo) != 0)
		return (1);
	pthread_mutex_lock(&(philo->main->print));
	printf("%d %d is sleeping\n", timestamp(philo->main), philo_no);
	pthread_mutex_unlock(&(philo->main->print));
	if (ft_sleep(philo, time_to_sleep) != 0)
		return (1);
	return (0);
}

static int	taking_forks_left(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	if (check_deaths(philo) != 0)
		return (pthread_mutex_unlock(philo->fork_left), 1);
	pthread_mutex_lock(&(philo->main->print));
	printf("%d %d has taken a fork\n", timestamp(philo->main), philo->id);
	pthread_mutex_unlock(&(philo->main->print));
	if (philo->left_available == false)
		return (pthread_mutex_unlock(philo->fork_left), 1);
	pthread_mutex_lock(&(philo->fork_right));
	if (check_deaths(philo) != 0)
		return (pthread_mutex_unlock(philo->fork_left),
			pthread_mutex_unlock(&(philo->fork_right)), 1);
	pthread_mutex_lock(&(philo->main->print));
	printf("%d %d has taken a fork\n", timestamp(philo->main), philo->id);
	pthread_mutex_unlock(&(philo->main->print));
	return (0);
}

static int	taking_forks(t_philo *philo)
{
	if (philo->id == philo->main->nb_philo && philo->main->nb_philo != 1)
	{
		if (taking_forks_left(philo) != 0)
			return (1);
	}
	else
	{
		pthread_mutex_lock(&(philo->fork_right));
		if (check_deaths(philo) != 0)
			return (pthread_mutex_unlock(&(philo->fork_right)), 1);
		pthread_mutex_lock(&(philo->main->print));
		printf("%d %d has taken a fork\n", timestamp(philo->main), philo->id);
		pthread_mutex_unlock(&(philo->main->print));
		if (philo->left_available == false)
			return (pthread_mutex_unlock(&(philo->fork_right)), 1);
		pthread_mutex_lock(philo->fork_left);
		if (check_deaths(philo) != 0)
			return (pthread_mutex_unlock(&(philo->fork_right)),
				pthread_mutex_unlock(philo->fork_left), 1);
		pthread_mutex_lock(&(philo->main->print));
		printf("%d %d has taken a fork\n", timestamp(philo->main), philo->id);
		pthread_mutex_unlock(&(philo->main->print));
	}
	return (0);
}

int	eating(t_philo *philo)
{
	if (taking_forks(philo) != 0)
		return (1);
	if (check_deaths(philo) != 0)
		return (pthread_mutex_unlock(&(philo->fork_right)),
			pthread_mutex_unlock(philo->fork_left), 1);
	pthread_mutex_lock(&(philo->meal));
	pthread_mutex_lock(&(philo->main->print));
	printf("%d %d is eating\n", timestamp(philo->main), philo->id);
	pthread_mutex_unlock(&(philo->main->print));
	philo->last_meal = timestamp(philo->main);
	philo->nb_meals += 1;
	pthread_mutex_lock(&(philo->main->loops));
	if (philo->nb_meals == philo->main->target_nb_of_meals)
		philo->main->finished_loops += 1;
	pthread_mutex_unlock(&(philo->main->loops));
	pthread_mutex_unlock(&(philo->meal));
	ft_sleep(philo, philo->main->time_to_eat);
	pthread_mutex_unlock(&(philo->fork_right));
	pthread_mutex_unlock(philo->fork_left);
	return (0);
}
