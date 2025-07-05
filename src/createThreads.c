/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createThreads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:37:26 by pmendez-          #+#    #+#             */
/*   Updated: 2025/07/05 19:02:29 by pmendez-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "philo.h"

static int check_philos_eaten(t_data *data)
{
	pthread_mutex_lock(&data->dead);
	if (data->meals == data->num_philos)
	{
		pthread_mutex_unlock(&data->dead);
		return (1);
	}
	pthread_mutex_unlock(&data->dead);
	return (0);
}

//TODO: Comprobar que el tiempo de muerte de cada filósofo no se ha superado
// static void check_time_dead(t_data *data)
// {
// 	unsigned long current;
// 	int	i;

// 	i = 0;
// 	current = get_time();
// 	while (i < data->num_philos)
// 	{
// 		pthread_mutex_lock(data->philo[i].dead);
// 		if (current - data->philo[i].last_meal >= data->philo[i].time_to_die)
// 		{
// 			*(data->philo[i].is_dead) = 1;
// 		}
// 		pthread_mutex_unlock(data->philo[i].dead);
// 		i++;
// 	}
// }

static int check_time_dead(t_data *data)
{
    unsigned long current;
    int i;

    i = 0;
    current = get_time();
    pthread_mutex_lock(&data->dead);
    while (i < data->num_philos)
    {
		// pthread_mutex_lock(data->philo[i].print);
		// printf("DEBUG: Soy el philo %d\n", data->philo[i].id_philo);
		// pthread_mutex_unlock(data->philo[i].print);
			
        if (current - data->philo[i].last_meal >= data->philo[i].time_to_die)
        {
            data->is_dead = 1;
			pthread_mutex_unlock(&data->dead);
            return (1);
        }
        i++;
    }
    pthread_mutex_unlock(&data->dead);
	return (0);
}

static void check_status(t_data *data)
{
	while (1)
	{
		if (check_time_dead(data) == 1)
			break;
		if (check_philos_eaten(data) == 1)
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
			print_and_free(data, "Error creating philosopher thread");
		i++;
	}
	pthread_mutex_unlock(&data->init);
	check_status(data);
}
