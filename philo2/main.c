/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:58:01 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/30 17:08:39 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!(str[i] >= '0' && str[i] < '9'))
			return (1);
		i++;
	}
	return (0);
}

int	check_args(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_isdigit(av[i]) == 1 || atoi(av[i]) < 0)
			return (printf("Please enter positive numbers only\n"), 1);
		i++;
	}
	if (atoi(av[1]) == 0)
		return (printf("Please create at least 1 philosopher\n"), 1);
	return (0);
}

int	main(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac < 5)
		printf("Not enough arguments\n");
	else if (ac > 6)
		printf("Too many arguments\n");
	else
	{
		if (check_args(av) != 0)
			return (1);
		if (initialize_main(ac, av) != 0)
			return (1);
	}
	return (0);
}
