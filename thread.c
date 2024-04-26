/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:14:43 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/26 16:22:42 by ctruchot         ###   ########.fr       */
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
		i++;
	}
	free(philo);
	free(th);
	if (pthread_mutex_destroy(main->death) != 0)
		return (printf("mutex destroy failed"), 1);
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
				return (printf("thread creation failed"), 1);
		}
		else
		{
			if (pthread_create(&th[i], NULL, &routine, &philo[i]) != 0)
				return (printf("thread creation failed"), 1);
		}
		i++;
	}
	end_thread(main, philo, th);
	return (0);
}
