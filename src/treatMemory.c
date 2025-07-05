/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatMemory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:05:51 by pmendez-          #+#    #+#             */
/*   Updated: 2025/07/05 17:34:48 by pmendez-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "philo.h"

static void	assign_mutex_death_times_to_philos(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philo[i].print = &(data->print);
		data->philo[i].init = &(data->init);
		data->philo[i].dead = &(data->dead);
		data->philo[i].fork_left = &(data->forks[i]);
		if (i == data->num_philos - 1)
			data->philo[i].fork_right = &(data->forks[0]);
		else
			data->philo[i].fork_right = &(data->forks[i + 1]);
		data->philo[i].is_dead = &(data->is_dead);
		data->philo[i].meals = &(data->meals);
		data->philo[i].nb_philos = data->num_philos;
		data->philo[i].last_meal = data->philo[i].start_time;
		i++;
	}
}

void	initialize_philos(t_data *data, char *argv[])
{
	int	i;

	i = 0;
	data->philo = ft_calloc(data->num_philos, sizeof(t_philo));
	if (!data->philo)
		print_and_free(data, RED "ERROR \n" RESET "Malloc failed\n");
	while (i < data->num_philos)
	{
		data->philo[i].id_philo = i + 1;
		data->philo[i].start_time = get_time();
		data->philo[i].time_to_die = ft_atoi(argv[2]);
		data->philo[i].time_to_eat = ft_atoi(argv[3]);
		data->philo[i].time_to_sleep = ft_atoi(argv[4]);
		if (argv[5])
			data->philo[i].times_each_philosopher_must_eat = ft_atoi(argv[5]);
		else
			data->philo[i].times_each_philosopher_must_eat = -1;
		i++;
	}
	assign_mutex_death_times_to_philos(data);
}

void	initialize_struct(t_data *data, char *argv[])
{
	int	i;

	i = 0;
	data->is_dead = 0;
	data->num_philos = ft_atoi(argv[1]);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->init, NULL);
	pthread_mutex_init(&data->dead, NULL);
	data->forks = ft_calloc(data->num_philos, sizeof(pthread_mutex_t));
	if (data->forks == NULL)
		print_and_free(data, "Error con los forks");
	while (i < data->num_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

void	free_struct(t_data *data)
{
	free(data->philo);
	if (data->num_philos > 0)
	{
		pthread_mutex_destroy(&data->print);
		pthread_mutex_destroy(&data->init);
		pthread_mutex_destroy(&data->dead);
		// pthread_mutex_destroy(&data->eat);
	}
	if (data->forks)
		free(data->forks);
}
