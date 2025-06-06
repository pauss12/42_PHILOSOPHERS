/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:05:51 by pmendez-          #+#    #+#             */
/*   Updated: 2025/06/06 14:14:29 by pmendez-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "philo.h"

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
		data->philo[i].times_eaten = 0;
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
}

//TODO: Inicializar los mutex de los tenedores
void	initialize_struct(t_data *data, char *argv[])
{
	int	i;

	i = 0;
	data->is_dead = 0;
	data->num_philos = ft_atoi(argv[1]);
	data->forks = ft_calloc(data->num_philos, sizeof(pthread_mutex_t));
	while (i < data->num_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->init, NULL);
}

void	free_struct(t_data *data)
{
	int	i;

	i = 0;
	if (data->philo)
	{
		while (i < data->num_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->philo);
	}
	if (data->forks)
		free(data->forks);
}
