/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:37:26 by pmendez-          #+#    #+#             */
/*   Updated: 2025/06/06 20:34:57 by pmendez-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "philo.h"

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
		pthread_mutex_lock(&data->dead);
		if (data->is_dead == 1)
		{
			pthread_mutex_unlock(&data->dead);
			return ;
		}
		pthread_mutex_unlock(&data->dead);
	}
}

void create_threads(t_data *data)
{
	int			i;

	i = 0;
	printf("Creating threads...\n");
	pthread_mutex_lock(&data->init);
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
