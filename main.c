/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:58:01 by ctruchot          #+#    #+#             */
/*   Updated: 2024/05/06 11:48:20 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

int	is_int(long long int n)
{
	if (n > INT_MAX || n < INT_MIN)
		return (1);
	return (0);
}

static int	check_args(int ac, char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_isdigit(av[i]) == 1 || ft_atoi(av[i]) < 0)
			return (printf("Please enter positive numbers only\n"), 1);
		if (is_int(ft_atoi(av[i])) == 1)
			return (printf("Please enter a number between %d and %d\n",
					INT_MIN, INT_MAX), 1);
		i++;
	}
	if (ft_atoi(av[1]) == 0)
		return (printf("Please create at least 1 philosopher\n"), 1);
	if (ac == 6 && ft_atoi(av[5]) == 0)
		return (printf("Please enter a positive number of meals\n"), 1);
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
		if (check_args(ac, av) != 0)
			return (1);
		if (initialize_main(ac, av) != 0)
			return (1);
	}
	return (0);
}
