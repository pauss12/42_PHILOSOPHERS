/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:03:49 by pmendez-          #+#    #+#             */
/*   Updated: 2025/07/19 17:24:01 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	t_data data;

	data = (t_data){0};
    if (check_args(argc, argv) == 1)
		return (1);
	initialize_struct(&data, argv);
	initialize_philos(&data, argv);
	create_threads(&data);
	printf("\n\nMAIN HAS FINISHED\n");

    return (0);
}

// static void	print_memory_add(t_data *data)
// {
// 	printf("pointer of mutex eat: %p\n", (void *)&data->eat);
// 	printf("pointer of EAT in philo %p\n\n", (void *)data->philo->eat);
// 	printf("pointer of mutex dead: %p\n", (void *)&data->dead);
// 	printf("pointer of DEAD in philo %p\n\n", (void *)data->philo->dead);
// 	printf("pointer of mutex init: %p\n", (void *)&data->init);
// 	printf("pointer of INIT in philo %p\n\n", (void *)data->philo->init);
// 	printf("pointer of mutex print: %p\n", (void *)&data->print);
// 	printf("pointer of PRINT in data %p\n\n", (void *)data->philo->print);
// }

// static void	print_addresses(t_philo *philo)
// {
// 	printf("pointer of EAT in philo %p\n\n", philo->eat);
// 	printf("pointer of DEAD in philo %p\n\n", philo->dead);
// 	printf("pointer of INIT in philo %p\n\n", philo->init);
// 	printf("pointer of PRINT in data %p\n\n", philo->print);
// }



//? GONZALO
// static int	time_checker(t_philo *philos)
// {
// 	pthread_mutex_lock(philos->meal);
// 	if (get_time() > philos->time_to_die)
// 	{
// 		pthread_mutex_unlock(philos->meal);
// 		return (0);
// 	}
// 	pthread_mutex_unlock(philos->meal);
// 	return (1);
// }

// int	check_philos(t_philo *philos)
// {
// 	int	i;

// 	i = 0;
// 	while (i < philos->nb_philos)
// 	{
// 		if (!time_checker(&philos[i]))
// 		{
// 			print_thread(&philos[i], philos[i].id, PHILO_DIE);
// 			pthread_mutex_lock(philos->dead);
// 			*philos[i].dead_flag = 1;
// 			pthread_mutex_unlock(philos->dead);
// 			return (0);
// 		}
// 		i++;
// 		usleep(10);
// 	}
// 	return (1);
// }