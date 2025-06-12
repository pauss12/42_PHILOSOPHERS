/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:05:51 by pmendez-          #+#    #+#             */
/*   Updated: 2025/06/12 20:36:33 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_mutex_to_philos(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philo[i].print = &data->print;
		data->philo[i].init = &data->init;
		data->philo[i].dead = &data->dead;
		data->philo[i].eat = &data->eat;
		i++;
	}
}

void	initialize_philos(t_data *data, char *argv[])
{
	int	i;

	i = 0;
	data->philo = ft_calloc(data->num_philos, sizeof(t_philo));
	if (!data->philo)
	{
		printf(RED "ERROR \n" RESET "Malloc failed\n");
		exit(1);
	}
	while (i < data->num_philos)
	{
		data->philo[i].id_philo = i + 1;
		data->philo[i].meals = &data->meals;
		data->philo[i].is_dead = &data->is_dead;
		data->philo[i].nb_philos = data->num_philos;
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
	assign_mutex_to_philos(data);
}

//TODO: Inicializar los mutex de los tenedores
void	initialize_struct(t_data *data, char *argv[])
{
	// int	i;

	// i = 0;
	data->is_dead = 0;
	data->num_philos = ft_atoi(argv[1]);
	// data->forks = ft_calloc(data->num_philos, sizeof(pthread_mutex_t));
	// while (i < data->num_philos)
	// {
	// 	pthread_mutex_init(&data->forks[i], NULL);
	// 	i++;
	// }
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->init, NULL);
	pthread_mutex_init(&data->dead, NULL);
	pthread_mutex_init(&data->eat, NULL);
}

void	free_struct(t_data *data)
{
	int	i;

	i = 0;
	// if (data->philo)
	// {
	// 	while (i < data->num_philos)
	// 	{
	// 		pthread_mutex_destroy(&data->forks[i]);
	// 		i++;
	// 	}
	// 	free(data->philo);
	// }
	// if (data->forks)
	// 	free(data->forks);
	if (data->philo)
	{
		while (i < data->num_philos)
		{
			pthread_mutex_destroy(data->philo[i].print);
			pthread_mutex_destroy(data->philo[i].init);
			pthread_mutex_destroy(data->philo[i].dead);
			pthread_mutex_destroy(data->philo[i].eat);
			i++;
		}
		free(data->philo);
	}
	if (data->num_philos > 0)
	{
		pthread_mutex_destroy(&data->print);
		pthread_mutex_destroy(&data->init);
		pthread_mutex_destroy(&data->dead);
		pthread_mutex_destroy(&data->eat);
	}
}
