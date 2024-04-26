/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:03:43 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/26 16:45:27 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int ac, char **av)
{
	if (ac == 5)
		if (atoi(av[1]) < 0 || atoi(av[2]) < 0 || atoi(av[3]) < 0
			|| atoi(av[4]) < 0)
			return (printf("please enter positive numbers\n"), 1);
	if (ac == 6)
	{
		if (atoi(av[1]) < 0 || atoi(av[2]) < 0 || atoi(av[3]) < 0
			|| atoi(av[4]) < 0 || atoi(av[5]) < 0)
			return (printf("please enter positive numbers\n"), 1);
	}
	else if (atoi(av[1]) == 0)
	{
		return (printf("please create at least 1 philosopher\n"), 1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_main	main;
	int		i;

	i = 0;
	if (ac < 5)
		printf("not enough arguments\n");
	else if (ac > 6)
		printf("too many arguments\n");
	else
	{
		if (check_args(ac, av) != 0)
			return (1);
		initialize_main(ac, av, &main);
		if (initialize_philo(&main) != 0)
			return (1);
	}
	return (0);
}
