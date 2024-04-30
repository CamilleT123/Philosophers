/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:13:18 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/30 17:51:13 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long int	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec) * 1000 + (current_time.tv_usec) / 1000);
}

int	timestamp(t_main *main)
{
	struct timeval	current_time;
	int				time_in_mili;

	gettimeofday(&current_time, NULL);
	time_in_mili = (current_time.tv_sec) * 1000 + (current_time.tv_usec) / 1000;
	return (time_in_mili - main->start_time);
}
