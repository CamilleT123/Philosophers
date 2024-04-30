/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:15:33 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/30 17:25:12 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_deaths(t_philo *philo)
{
	pthread_mutex_lock(&philo->main->death);
	if (philo->main->someone_died == 1)
		return (pthread_mutex_unlock(&philo->main->death), 1);
	pthread_mutex_unlock(&philo->main->death);
	if (philo->main->finished_loop >= philo->main->nb_philo)
		return (1);
	pthread_mutex_lock(&philo->main->death);
	if (((get_time() - philo->last_meal) >= philo->main->time_to_die))
	{
		printf("%lld %d died\n", get_time(), philo->id);
		philo->main->someone_died = 1;
		return (pthread_mutex_unlock(&philo->main->death), 1);
	}
	pthread_mutex_unlock(&philo->main->death);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	philo;

	philo = *(t_philo *)arg;
	if (check_deaths(&philo) != 0)
		return (NULL);
	if (!(philo.id % 2))
		if (eating(&philo) != 0)
			return (NULL);
	while (!philo.main->someone_died)
	{
		if (thinking(&philo, philo.id) != 0)
			return (NULL);
		if (eating(&philo) != 0)
			return (NULL);
		if (sleeping(&philo, philo.main->time_to_sleep, philo.id) != 0)
			return (NULL);
	}
	return (NULL);
}

void	*routine_for_1(void *arg)
{
	t_philo	philo;

	philo = *(t_philo *)arg;
	while (1)
	{
		if (check_deaths(&philo) != 0)
			return (NULL);
	}
	return (NULL);
}

// void	*monitoring(void *arg)
// {
// 	t_philo *philos;
// 	int i;
	
// 	philos = (t_philo *)arg;
// 	i = 0;
// 	while(!philos[0].main->someone_died)
// 	{
// 		while (i < philos[0].main->nb_philo)
// 		{
// 			// printf("%d last meal = %lld\n", philos[i].id, philos[i].last_meal);
// 			// pthread_mutex_lock(&(philos[i].meal));
// 			if ((get_time() - philos[i].last_meal) >= philos[0].main->time_to_die)
// 			{
// 				printf("%d last meal = %lld\n", philos[i].id, philos[i].last_meal);
// 				printf("%d philo add = %p\n", philos[i].id, &(philos[i]));
// 				printf("%lld %d diiied\n", get_time(), philos[i].id);
// 				philos[0].main->someone_died = 1;
// 				return (NULL);				
// 			}
// 			// pthread_mutex_unlock(&(philos[i].meal));
// 			i++;
// 		}
// 		usleep(300);
// 		i = 0;
// 	}
// 	return (NULL);
// }

