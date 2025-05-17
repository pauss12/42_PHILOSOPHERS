/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paulamendezsv@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:37:26 by paula             #+#    #+#             */
/*   Updated: 2025/05/17 22:44:46 by paula            ###   ########.fr       */
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
			//free_struct(data);
		}
		i++;
	}
	ft_printf("All threads joined successfully.\n");
}



void create_threads(t_data *data)
{
	int			i;

	i = 0;
	ft_printf("Creating threads...\n");
	pthread_mutex_lock(&data->init);
	while (i < data->num_philos)
	{
		data->philo[i].data = (struct t_data *)data;
		if (pthread_create(&data->philo[i].thread, NULL, routine, &data->philo[i]) != 0)
		{
			print_error("Error creating philosopher thread");
		}
		i++;
	}
	printf("Threads created successfully.\n");
	pthread_mutex_unlock(&data->init);

	//Comprueba si alguien ha muerto
	check_status(data);

	// Wait for all threads to finish
	wait_for_threads(data);
}
