/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createThreads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:37:26 by pmendez-          #+#    #+#             */
/*   Updated: 2025/06/28 21:13:31 by pmendez-         ###   ########.fr       */
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

//TODO: Comprobar que el tiempo de muerte de cada filósofo no se ha superado
static void check_time_dead(t_data *data)
{
	int	i;

	i = 0;
	printf("Checking time dead\n");
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->dead);
		if (get_time() > data->philo[i].time_to_die)
		{
			data->is_dead = 1;
			pthread_mutex_unlock(&data->dead);
			return ;
		}
		pthread_mutex_unlock(&data->dead);
		i++;
	}
}

static void check_status(t_data *data)
{
	while (1)
	{

		printf("HELOOO\n");
		if (data->num_philos == 1)
		{
			pthread_mutex_lock(&data->dead);
			data->is_dead = 1;
			pthread_mutex_unlock(&data->dead);
			break ;
		}
		check_time_dead(data);
		if (check_philos_eaten(data) == 1)
			break ;
		if (check_philo_dead(data) == 1)
			break ;
		usleep(10);
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
}
