/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:17:35 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/30 18:31:54 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	end_thread(t_main *main, t_philo *philo, pthread_t *th)
{
	int	i;

	i = 0;
	while (i < main->nb_philo)
	{
		if (pthread_join(th[i], NULL) != 0)
			return (printf("thread joining failed"), 1);
		i++;
	}
	i = 0;
	while (i < main->nb_philo)
	{
		if (pthread_mutex_destroy(philo[i].fork_right) != 0)
			return (printf("mutex destroy failed"), 1);
		free(philo[i].fork_right);
		if (pthread_mutex_destroy(&(philo[i].meal)) != 0)
			return (printf("mutex destroy failed"), 1);
		i++;
	}
	if (pthread_mutex_destroy(&(main->death)) != 0)
		return (printf("mutex destroy failed"), 1);
	free(philo);
	free(th);
	free(main);
	return (0);
}

int	monitoring(t_main *main, t_philo *philo)
{
	int	i;

	i = 0;
	while (main->finished_loops < main->nb_philo)
	{
		while (i < main->nb_philo)
		{
			pthread_mutex_lock(&(philo[i].meal));
			if ((timestamp(philo->main) - philo[i].last_meal)
				>= main->time_to_die)
			{
				pthread_mutex_lock(&(philo[i].main->death));
				printf("%d %d diiied\n", timestamp(philo->main), philo[i].id);
				main->someone_died = 1;
				pthread_mutex_unlock(&(philo[i].main->death));
				return (pthread_mutex_unlock(&(philo[i].meal)), 1);
			}
			pthread_mutex_unlock(&(philo[i].meal));
			i++;
		}
		usleep(2000);
		i = 0;
	}
	return (0);
}

int	create_thread(t_main *main, t_philo *philo)
{
	pthread_t	*th;
	int			i;

	i = 0;
	th = malloc(sizeof(pthread_t) * main->nb_philo);
	if (!th)
		return (1);
	while (i < main->nb_philo)
	{
		if (main->nb_philo == 1)
		{
			if (pthread_create(&th[i], NULL, &routine_for_1, &philo[i]) != 0)
				return (printf("thread creation failed\n"), 1);
		}
		else
		{
			if (pthread_create(&th[i], NULL, &routine, &(philo[i])) != 0)
				return (printf("thread creation failed\n"), 1);
		}
		i++;
	}
	monitoring(main, philo);
	end_thread(main, philo, th);
	return (0);
}
