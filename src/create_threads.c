/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paulamendezsv@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:37:26 by paula             #+#    #+#             */
/*   Updated: 2025/05/12 21:25:24 by paula            ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "philo.h"

static void wait_for_threads(t_data *data, pthread_t monitor)
{
	int			i;
	if (pthread_join(monitor, NULL) != 0)
	{
		print_error("Error joining monitor thread");
		free_struct(data);
	}
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
		{
			print_error("Error joining philosopher thread");
			free_struct(data);
		}
		i++;
	}
}

void create_threads(t_data *data)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	if (pthread_create(&monitor, NULL, monitoring, data) != 0)
	{
		print_error("Error creating monitor thread");
		return ;
	}
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philo[i].thread, NULL, routine, &data->philo[i]) != 0)
		{
			print_error("Error creating philosopher thread");
			free_struct(data);
		}
		i++;
	}
	wait_for_threads(data, monitor);
}
