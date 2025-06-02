/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:16:09 by paula             #+#    #+#             */
/*   Updated: 2025/06/02 20:37:01 by pmendez-         ###   ########.fr       */
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

//TODO: Si devuelve 1, ha fallado
int eating(t_philo *philo)
{
	// Checkear si philo ha activado is_dead a 1.
	if (check_if_philo_dead(philo->data) == 1)
		return (1);
	
	//Coger tenedores

	// Comprobar la ultima vez que ha comido

	// Imprimir mensaje de comida

	// Hacer el tiempo de comer -----

	// Liberar tenedores

	// Comprobar si ha comido el numero de veces que se le ha indicado
	if (philo->times_eaten >= philo->times_each_philosopher_must_eat)
		return (1);
	return (0);
}

void *routine(void *arg)
{
	t_data		*data;
	t_philo		*philo;

	philo = (t_philo *)arg;
	data = (t_data *)philo->data;

	//El hilo se queda bloqueado aqui
	pthread_mutex_lock(&data->init);
	pthread_mutex_unlock(&data->init);


	while (1)
	{
		print_message_philo(philo, "has started routine");
		printf("jdnnskdfnc\n");
		
		if (eating(philo) == 1)
			return (NULL);

		// Dormir
		

		// Pensar

		if (data->is_dead == 1)
			break ;
	}
	return (NULL);
}

//TODO: Hacer bucle infinito para imprimir los mensajes igual, pero en un tiempo especifico (valor de argv[5]). 
//TODO: Si se pasa ese tiempo, acaba el programa.

//caso prueba: ./philo 2 60 120 10 
// 