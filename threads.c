/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:17:35 by ctruchot          #+#    #+#             */
/*   Updated: 2024/05/06 14:51:38 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	destroy_mutexes(t_main *main, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < main->nb_philo)
	{
		if (pthread_mutex_destroy(&(philo[i].fork_right)) != 0)
			printf("mutex destroy failed");
		if (pthread_mutex_destroy(&(philo[i].meal)) != 0)
			printf("mutex destroy failed");
		i++;
	}
	if (pthread_mutex_destroy(&(main->death)) != 0)
		printf("mutex destroy failed");
	if (pthread_mutex_destroy(&(main->loops)) != 0)
		printf("mutex destroy failed");
	if (pthread_mutex_destroy(&(main->print)) != 0)
		printf("mutex destroy failed");
	return (0);
}

static int	end_thread(t_main *main, t_philo *philo, pthread_t *th, int err)
{
	int	i;

	i = 0;
	while (i < err)
	{
		if (pthread_join(th[i], NULL) != 0)
			printf("thread joining failed");
		i++;
	}
	destroy_mutexes(main, philo);
	free(philo);
	free(th);
	free(main);
	return (0);
}

static int	monitoring_loop(t_main *main, t_philo *philo, int i)
{
	pthread_mutex_lock(&(philo[i].meal));
	if ((timestamp(philo->main) - philo[i].last_meal)
		>= main->time_to_die)
	{
		pthread_mutex_unlock(&(philo[i].meal));
		pthread_mutex_lock(&(philo[i].main->death));
		if (main->someone_died == 1)
			return (pthread_mutex_unlock(&(philo[i].main->death)), 1);
		pthread_mutex_lock(&(main->print));
		printf("%d %d died\n", timestamp(philo->main), philo[i].id);
		pthread_mutex_unlock(&(main->print));
		main->someone_died = 1;
		return (pthread_mutex_unlock(&(philo[i].main->death)), 1);
	}
	pthread_mutex_unlock(&(philo[i].meal));
	return (0);
}

static int	monitoring(t_main *main, t_philo *philo)
{
	int	i;

	pthread_mutex_lock(&(main->loops));
	while (main->finished_loops < main->nb_philo)
	{
		pthread_mutex_unlock(&(main->loops));
		i = -1;
		while (++i < main->nb_philo)
			if (monitoring_loop(main, philo, i) != 0)
				return (1);
		pthread_mutex_lock(&(main->loops));
	}
	pthread_mutex_unlock(&(main->loops));
	return (0);
}

int	create_thread(t_main *main, t_philo *philo)
{
	pthread_t	*th;
	int			i;

	i = 0;
	th = malloc(sizeof(pthread_t) * main->nb_philo);
	if (!th)
		return (pthread_mutex_destroy(&(philo[i].fork_right)),
			pthread_mutex_destroy(&(philo[i].meal)), 1);
	while (i < main->nb_philo)
	{
		if (pthread_create(&th[i], NULL, &routine, &(philo[i])) != 0)
		{
			printf("thread creation failed\n");
			end_thread(main, philo, th, i);
			return (0);
		}
		i++;
	}
	monitoring(main, philo);
	end_thread(main, philo, th, main->nb_philo);
	return (0);
}
