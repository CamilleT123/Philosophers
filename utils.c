/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:52:47 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/22 20:04:52 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long int	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	// return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
		// in millisec
	return ((current_time.tv_sec * 1000000) + (current_time.tv_usec));
		// in microsecs
}
