/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paulamendezsv@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:16:09 by paula             #+#    #+#             */
/*   Updated: 2025/05/17 22:45:38 by paula            ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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

void *routine(void *arg)
{
	t_data		*data;
	t_philo		*philo;

	philo = (t_philo *)arg;
	data = (t_data *)philo->data;

	//EL hilo se queda bloqueado aqui
	pthread_mutex_lock(&data->init);
	pthread_mutex_unlock(&data->init);
	
	if (philo->id_philo == 1)
	{
		print_message(philo, "A -");
	}
	else if (philo->id_philo == 2)
	{
		usleep(1000);
		print_message(philo, "B -");
	}
	else if (philo->id_philo == 3)
	{
		usleep(2000);
		print_message(philo, "C -");
	}

	return (NULL);
}



// printf("El valor es: %d\n", data->valor);
// data->valor++;
//printf("im here\n");
// printf("El valor DESPUES : %d\n", data->valor);