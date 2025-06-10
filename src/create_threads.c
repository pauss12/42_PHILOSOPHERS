/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:37:26 by pmendez-          #+#    #+#             */
/*   Updated: 2025/06/10 21:07:21 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static int check_philos_eaten(t_data *data)
{
	pthread_mutex_lock(&data->eat);
	if (data->meals == data->num_philos)	
	{
		pthread_mutex_unlock(&data->eat);
		return (1);
	}
	pthread_mutex_unlock(&data->eat);
	return (0);
}


static int check_philo_dead(t_data *data)
{
	pthread_mutex_lock(&data->dead);
	if (data->is_dead == 1)
	{
		pthread_mutex_unlock(&data->dead);
		return (1);
	}
	pthread_mutex_unlock(&data->dead);
	return (0);
}

static void wait_for_threads(t_data *data)
{
	int			i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
		{
			pthread_mutex_lock(&data->print);
			print_error("Error joining philosopher thread");
			pthread_mutex_unlock(&data->print);
		}
		i++;
	}
	printf("All threads joined successfully.\n");
}

static void check_status(t_data *data)
{
	while (1)
	{	
		if (check_philos_eaten(data))
			return ;
		if (check_philo_dead(data))
			return ;
	
		usleep(1000); // Sleep for a short time to avoid busy waiting
		//printf("Checking status...\n");
	}
}

// static void	print_memory_add(t_data *data)
// {
// 	printf("pointer of mutex eat: %p\n", (void *)&data->eat);
// 	printf("pointer of EAT in philo %p\n\n", (void *)data->philo->eat);
	

// 	printf("pointer of mutex dead: %p\n", (void *)&data->dead);
// 	printf("pointer of DEAD in philo %p\n\n", (void *)data->philo->dead);

// 	printf("pointer of mutex init: %p\n", (void *)&data->init);
// 	printf("pointer of INIT in philo %p\n\n", (void *)data->philo->init);


// 	printf("pointer of mutex print: %p\n", (void *)&data->print);
// 	printf("pointer of PRINT in data %p\n\n", (void *)data->philo->print);
// }

void create_threads(t_data *data)
{
	int			i;

	i = 0;
	printf("Creating threads...\n");
	pthread_mutex_lock(&data->init);
	// print_memory_add(data);
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philo[i].thread, NULL, routine, &data->philo[i]) != 0)
			print_error("Error creating philosopher thread");
		i++;
	}
	printf("Threads created successfully.\n");
	pthread_mutex_unlock(&data->init);

	check_status(data);
	wait_for_threads(data);
}
