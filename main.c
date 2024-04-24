/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:03:43 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/24 11:12:39 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		initialize_main(ac, av, &main);
		initialize_philo(&main);
	}
	return (0);
}
