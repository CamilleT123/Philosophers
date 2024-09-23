/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:20:35 by ctruchot          #+#    #+#             */
/*   Updated: 2024/05/06 14:29:34 by ctruchot         ###   ########.fr       */
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
	pthread_mutex_lock(&main->loops);
	if (main->finished_loops >= main->nb_philo)
		return (pthread_mutex_unlock(&main->loops), 1);
	pthread_mutex_unlock(&main->loops);
	pthread_mutex_lock(&(philo->meal));
	if (((timestamp(main) - philo->last_meal) >= main->time_to_die))
	{
		pthread_mutex_unlock(&(philo->meal));
		pthread_mutex_lock(&(philo->main->print));
		pthread_mutex_lock(&main->death);
		printf("%d %d died\n", timestamp(main), philo->id);
		pthread_mutex_unlock(&(philo->main->print));
		main->someone_died = 1;
		return (pthread_mutex_unlock(&main->death), 1);
	}
	pthread_mutex_unlock(&(philo->meal));
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (check_deaths(philo) != 0)
		return (NULL);
	if (philo->id % 2 && philo->main->nb_philo != 1)
	{
		if (thinking(philo, philo->id) != 0)
			return (NULL);
		ft_sleep(philo, philo->main->time_to_eat / 2);
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
