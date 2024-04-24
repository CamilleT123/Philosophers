/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:14:43 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/24 13:25:20 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
// &th[i] == th + i

int	create_thread(t_main *main, t_philo *philo)
{
	pthread_t	*th;
	pthread_mutex_t mutex;
	int			i;

	i = 0;
	th = malloc(sizeof(pthread_t) * main->nb_philo);
		if (!th)
		return (1);
	pthread_mutex_init(&mutex, NULL);
	// pthread_mutex_init(&main->mutex, NULL);
	while (i < main->nb_philo)
	{
		// printf("1philo[%d].fork_right=%d\n", i, *(philo[i].fork_right));
		// printf("1philo[%d].fork_left=%d\n", i, *(philo[i].fork_right));
		philo[i].which_thread = 1;
		if (pthread_create(&th[i], NULL, &routine, philo) != 0)
			return (printf("failed"), 1);
		philo[i].which_thread = 0;
		printf("thread %d has started\n", i);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	// pthread_mutex_init(&main->mutex, NULL);
	end_thread(main, philo, th);
	return (0);
}

int	end_thread(t_main *main, t_philo *philo, pthread_t *th)
{
	int	i;

	i = 0;
	while (i < main->nb_philo)
	{
		if (pthread_join(th[i], NULL) != 0)
			return (1);
		printf("thread %d has finished\n", i);
		// if (philo[i].fork_right)
		// {
		// 	free(philo[i].fork_right);
		// 	philo[i].fork_right = NULL;
		// }
		i++;
	}
	free(philo);
	free(th);
	return (0);
}
