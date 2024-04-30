/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:14:43 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/29 16:30:18 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// &th[i] == th + i

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


int monitoring(t_main *main, t_philo *philo)
{
	int i;
	
	i = 0;
	while(!main->someone_died)
	{
		while (i < main->nb_philo)
		{
			// printf("%d last meal = %lld\n", philos[i].id, philos[i].last_meal);
			pthread_mutex_lock(&(philo[i].meal));
			if ((get_time() - philo[i].last_meal) >= main->time_to_die)
			{
				printf("%d last meal = %lld\n", philo[i].id, philo[i].last_meal);
				// printf("%d philo add = %p\n", philo[i].id, &(philos[i]));
				printf("%lld %d diiied\n", get_time(), philo[i].id);
				main->someone_died = 1;
				return (0);			
			}
			pthread_mutex_unlock(&(philo[i].meal));
			i++;
		}
		usleep(300);
		i = 0;
	}
	return (0);
}


int	create_thread(t_main *main, t_philo *philo)
{
	pthread_t	*th;
	int			i;

	i = 0;
	th = malloc(sizeof(pthread_t) * (main->nb_philo + 1));
	if (!th)
		return (1);
	while (i < main->nb_philo)
	{
		if (main->nb_philo == 1)
		{
			if (pthread_create(&th[i], NULL, &routine_for_1, &philo[i]) != 0)
				return (printf("thread creation failed"), 1);
		}
		else
		{
			if (pthread_create(&th[i], NULL, &routine, &philo[i]) != 0)
				return (printf("thread creation failed"), 1);
		}
		i++;
	}
	// if (pthread_create(&th[i], NULL, &monitoring, philo) != 0)
	// 			return (printf("thread creation failed"), 1);
	monitoring(main, philo);
	end_thread(main, philo, th);
	return (0);
}
