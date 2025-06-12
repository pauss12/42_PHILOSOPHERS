/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:16:09 by pmendez-          #+#    #+#             */
/*   Updated: 2025/06/12 20:12:59 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	sleeping(t_data *data)
// {
// 	long start_time;

// 	start_time = get_time();
// 	while (get_time() - start_time < data->philo->time_to_sleep)
// 	{
// 		if (data->philo->is_dead == 1)
// 			return (NULL);
// 		usleep(100);
// 	}
// }

static int eaten(t_philo *philo)
{
	pthread_mutex_lock(philo->eat);
	if (philo->times_each_philosopher_must_eat != -1)
	{
		philo->times_each_philosopher_must_eat--;
		if (philo->times_each_philosopher_must_eat == 0)
		{
			*philo->meals += 1;
			pthread_mutex_unlock(philo->eat);
			return (1);
		}
	}
	pthread_mutex_unlock(philo->eat);
	return (0);
}

//TODO: Si devuelve 1, ha fallado
int eating(t_philo *philo)
{
	// if (check_if_philo_dead(philo) == 1)
	// 	return (1);

	// Comprobar si ha comido el numero de veces que se le ha indicado
	if (eaten(philo) == 1)
		return (1);
	
	return (0);
}

void *routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->init);
	pthread_mutex_unlock(philo->init);
	while (check_if_philo_dead(philo) == 0)
	{
		print_message_philo(philo, "has started routine");
		
		if (eating(philo) == 1)
			return (NULL);

		// Dormir
		

		// Pensar
		/* if (!check_if_philo_dead(philo))
			return NULL; */
	}
	return (NULL);
}

//caso prueba: ./philo 2 60 120 10 

// static void	print_addresses(t_philo *philo)
// {
// 	printf("pointer of EAT in philo %p\n\n", philo->eat);
// 	printf("pointer of DEAD in philo %p\n\n", philo->dead);
// 	printf("pointer of INIT in philo %p\n\n", philo->init);
// 	printf("pointer of PRINT in data %p\n\n", philo->print);
// }
