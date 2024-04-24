/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:15:33 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/24 13:24:25 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int sleeping(t_main *main, int time_to_sleep, int philo_no)
{
	printf("%lld milisec: %d is sleeping\n", ((get_time() - main->start_time)/1000), philo_no);
	usleep(time_to_sleep * 1000);
	// printf("%lld milisec: %d woke up\n", ((get_time() - main->start_time )/1000), philo_no);
	return (0);
}

// int eating(t_philo *philo, t_main *main, int , int philo_id)
int eating(t_philo *philo)
{
	// printf("philo[%d].fork_right=%d\n", philo->id, *(philo->fork_right));
	// printf("philo[%d].fork_left=%d\n", philo->id, *(philo->fork_left));
	while (!(philo->fork_right == FREE) && !(philo->fork_left == FREE))
		usleep(100);
		// printf("philo[%d] right fork available\n", philo->id);
		// printf("philo[%d] left fork available\n", philo->id);
	printf("%lld milisec: %d has taken 2 forks\n", ((get_time() - philo->main->start_time)/1000), philo->id);
	philo->fork_right = BUSY;
	philo->fork_left = BUSY;
		// printf("philo[%d].fork_right=%d\n", philo->id, *(philo->fork_right));
		// printf("philo[%d].fork_left=%d\n", philo->id, *(philo->fork_right));
	printf("%lld milisec: %d is eating\n", ((get_time() - philo->main->start_time)/1000), philo->id);
	usleep(philo->main->time_to_eat * 1000);
	philo->last_meal = get_time();
	// printf("%d last_meal= %lld\n", philo->id, philo->last_meal);
	philo->fork_right = FREE;
	philo->fork_left = FREE;
	printf("%lld milisec: %d puts back 2 forks\n", ((get_time() - philo->main->start_time)/1000), philo->id);
	// printf("philo[%d].fork_right=%d\n", philo->id, *(philo->fork_right));
	return (0);
}

int thinking(t_philo *philo, int philo_no)
{
	printf("%lld milisec: %d is thinking\n", ((get_time() - philo->main->start_time)/1000), philo_no);
	while (!(philo->fork_right == FREE) && !(philo->fork_left == FREE))
	{
		printf("LAAA\n");
		usleep(100);
	}
	printf("ICII\n");
	return (0);
}

void *routine(void *arg)
{
	t_philo *philo = (t_philo*)arg;
	int i = 0;
	printf("4. philo id =%d\n", philo[0].id);
	printf("4. philo id =%d\n", philo[1].id);
	while (i < philo[0].main->nb_philo)
	{
		if (philo[i].which_thread == 1)
		printf("4. which thread =%d\n", i);
		i++;
	}
	// printf("5. last_meal= %lld\n", philo.last_meal);
	// // printf("gettime=%lld\n", get_time());
	// printf("time to die= %d\n", philo.main->time_to_die);
	// printf("6. premier tour = %lld\n", (get_time() - philo.last_meal)/1000);
	// // while ((((get_time() - philo.last_meal)/1000) < philo.main->time_to_die))
	// while ((((get_time() - philo.last_meal)/1000) < philo.main->time_to_die) 
	// 	&& (philo.main->check_nb_of_eat == 1 && i <= philo.main->nb_of_eat))
	// {
	// 	eating(&philo);
	// 	sleeping(philo.main, philo.main->time_to_sleep, philo.id);
	// 	thinking(&philo, philo.id);
	// // 	// printf("gettime=%d\n", get_time());
	// // 	// printf("%d last_meal= %d\n", philo.id, philo.last_meal);
	// // 	// printf("%d time since last_meal= %lld\n", philo.id, (get_time() - philo.last_meal)/1000);
	// 	i++;
	// }	
	// printf("%lld milisec: %d died\n", ((get_time() - philo.main->start_time)/1000), philo.id);
	// printf("time_to_sleep=%d\n", main.time_to_sleep);
	// take_fork();
	// eat(main.time_to_eat);
	// thinks(main.time_to_sleep);
	return (0);
}
