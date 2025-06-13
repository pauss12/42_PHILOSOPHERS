/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createThreads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:37:26 by pmendez-          #+#    #+#             */
/*   Updated: 2025/06/13 17:27:41 by pmendez-         ###   ########.fr       */
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
}

static void check_status(t_data *data)
{
	while (1)
	{	
		if (check_philos_eaten(data) || check_philo_dead(data))
			break ;
	}
}

void create_threads(t_data *data)
{
	t_philo	*philo2;
	int		i;

	i = 0;
	pthread_mutex_lock(&data->init);
	while (i < data->num_philos)
	{
		philo2 = &data->philo[i];
		if (pthread_create(&philo2->thread, NULL, routine, philo2) != 0)
			print_and_free(data);
		i++;
	}
	pthread_mutex_unlock(&data->init);
	check_status(data);
	wait_for_threads(data);
}
