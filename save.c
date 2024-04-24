
// int create_philo(t_main *main)
// {
// 	pthread_t th[main->nb_philo];
// 	int i;

// 	i = 0;
// 	while (i < main->nb_philo)
// 	{
// 		main->philo_no = malloc(sizeof(int));
// 		*main->philo_no = i;
// 		printf("i=%d\n", i);
// 		if (pthread_create(&th[i], NULL, &routine, main) != 0) // &th[i] == th + i
// 			return (printf("failed"), 1);
// 		printf("thread %d has started\n", i);
// 		i++;
// 	}
// 	while (i-- > 0)
// 	{
// 		if (pthread_join(th[i], NULL) != 0)
// 			return (1);
// 		printf("thread %d has finished\n", i);
// 	}
// 	return (0);
// }


// int create_philo(t_main *main)
// {
// 	pthread_t th[main->nb_philo];
// 	int i;

// 	i = 0;
// 	while (i < main->nb_philo)
// 	{
// 		int *a = malloc(sizeof(int));
// 		*a = i;
// 		t_philo philo[*a];

// 		printf("i=%d\n", i);
// 		philo[*a].main = main;
// 		philo[*a].philo_no = i;
// 		printf("philo_no=%d\n", philo[*a].philo_no);
// 		if (pthread_create(&th[i], NULL, &routine, &philo[*a]) != 0) // &th[i] == th + i
// 			return (printf("failed"), 1);
// 		printf("thread %d has started\n", i);
// 		i++;
// 	}
// 	while (i-- > 0)
// 	{
// 		printf("i2=%d\n", i);
// 		if (pthread_join(th[i], NULL) != 0)
// 			return (1);
// 		printf("thread %d has finished\n", i);
// 	}
// 	return (0);
// }
