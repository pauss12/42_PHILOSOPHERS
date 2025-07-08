/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createThreads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:37:26 by pmendez-          #+#    #+#             */
/*   Updated: 2025/07/08 19:05:42 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
//TODO: No detecta bien la muerte ---------------
static int check_time_dead(t_data *data)
{
    unsigned long current;
    int i;

    i = 0;
    while (i < data->num_philos)
    {
		pthread_mutex_lock(&data->eat);
		current = get_time();
        if (current - data->philo[i].last_meal >= data->philo[i].time_to_die)
        {
			pthread_mutex_lock(&data->print);
			printf(RED BOLD "PHILO %d HAS DIED 💀\n" RESET, data->philo->id_philo);
			pthread_mutex_unlock(&data->print);

			pthread_mutex_lock(&data->dead);
            data->is_dead = 1;
		    pthread_mutex_unlock(&data->dead);

            return (1);
        }
		usleep(10);
        i++;
    }
    pthread_mutex_unlock(&data->dead);
	return (0);
}

static void *check_status(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_philos_eaten(data) == 1)
			break ;
		if (check_time_dead(data) == 1)
			break ;
		usleep(10);
	}
	return (NULL);
}

void create_threads(t_data *data)
{
	pthread_t	monitor;
	t_philo		*philo2;
	int		i;

	i = 0;
	pthread_mutex_lock(&data->init);
	if (pthread_create(&monitor, NULL, check_status, data) != 0)
		print_and_free(data, "Error creating monitor thread");
	while (i < data->num_philos)
	{
		philo2 = &data->philo[i];
		if (pthread_create(&philo2->thread, NULL, routine, philo2) != 0)
			print_and_free(data, "Error creating philosopher thread");
		i++;
	}
	pthread_mutex_unlock(&data->init);
	check_status(data);
	printf("SALEEEEE\n");
	if (pthread_join(monitor, NULL) != 0)
		print_and_free(data, "Error joining monitor thread");
	wait_for_threads(data);
	printf("\nHa esperado a los philos\n");
}
