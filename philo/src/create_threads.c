/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createThreads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:14:23 by pmendez-          #+#    #+#             */
/*   Updated: 2025/09/27 19:16:59 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	check_philos_eaten(t_data *data)
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

static int	checking_time(t_data *data, t_philo *philo)
{
	unsigned long	last_meal;
	unsigned long	time_to_die;

	pthread_mutex_lock(philo->eat);
	last_meal = philo->last_meal;
	time_to_die = philo->time_to_die;
	pthread_mutex_unlock(philo->eat);
	if (get_time() - last_meal > time_to_die)
	{
		pthread_mutex_lock(&data->dead);
		data->is_dead = 1;
		pthread_mutex_unlock(&data->dead);
		return (1);
	}
	return (0);
}

static int	check_time_dead(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->dead);
	if (data->is_dead == 1)
	{
		pthread_mutex_unlock(&data->dead);
		return (1);
	}
	pthread_mutex_unlock(&data->dead);
	while (i < data->num_philos)
	{
		if (checking_time(data, &(data->philo[i])) == 1)
		{
			pthread_mutex_lock(&data->print);
			printf(RED"%lu %d %s\n"RESET, \
			get_time() - data->philo[i].start_time, \
			data->philo[i].id_philo, DIED);
			pthread_mutex_unlock(&data->print);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	*check_status(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_philos_eaten(data) == 1)
			return (NULL);
		if (check_time_dead(data) == 1)
			return (NULL);
		usleep(9);
	}
	return (NULL);
}

void	create_threads(t_data *data)
{
	pthread_t	monitor;
	t_philo		*philo2;
	int			i;

	i = 0;
	pthread_mutex_lock(&data->init);
	if (pthread_create(&monitor, NULL, check_status, data) != 0)
		print_and_free(data, "Error creating monitor thread");
	while (i < data->num_philos)
	{
		philo2 = &data->philo[i];
		if (pthread_create(&philo2->thread, NULL, routine, philo2) != 0)
		{
			pthread_mutex_unlock(&data->init);
			print_and_free(data, "Error creating philosopher thread");
		}
		i++;
	}
	pthread_mutex_unlock(&data->init);
	if (pthread_join(monitor, NULL) != 0)
		print_and_free(data, "Error joining monitor thread");
	wait_for_threads(data);
	free_struct(data);
}
