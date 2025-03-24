/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:05:51 by pmendez-          #+#    #+#             */
/*   Updated: 2025/03/24 20:05:52 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	initialize_philos(t_data *data)
{
	int i;

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
		data->philo[i].is_dead = 0;
		i++;
	}
}

//TODO: Inicializar los mutex de los tenedores
void	initialize_struct(t_data *data, char *argv[])
{
	int i;

	i = 0;
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->num_eat = ft_atoi(argv[5]);
	else
		data->num_eat = -1;
	data->forks = ft_calloc(data->num_philos, sizeof(pthread_mutex_t));
	while (i < data->num_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	initialize_philos(data);
}

