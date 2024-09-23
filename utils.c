/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:13:18 by ctruchot          #+#    #+#             */
/*   Updated: 2024/05/06 15:33:50 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_sleep(t_philo *philo, int time_to_sleep)
{
	int			time;
	long long	start_time;

	start_time = get_time();
	time = 0;
	while (time < time_to_sleep)
	{
		if (check_deaths(philo) != 0)
			return (1);
		usleep(1000);
		time = get_time() - start_time;
	}
	return (0);
}

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

long long int	ft_atoi(const char *nptr)
{
	long long int	r;
	int				rneg;
	int				i;

	r = 0;
	i = 0;
	rneg = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			rneg = rneg * -1;
		i++;
	}
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		r = r * 10 + nptr[i] - 48;
		i++;
	}
	if (rneg == -1)
		r = r * -1;
	return (r);
}
