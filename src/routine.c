/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:16:09 by paula             #+#    #+#             */
/*   Updated: 2025/06/01 18:31:04 by pmendez-         ###   ########.fr       */
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

// void *routine(void *arg)
// {
// 	t_data		*data;
// 	t_philo		*philo;

// 	philo = (t_philo *)arg;
// 	data = (t_data *)philo->data;

// 	//EL hilo se queda bloqueado aqui
// 	pthread_mutex_lock(&data->init);
// 	pthread_mutex_unlock(&data->init);
	
// 	if (philo->id_philo == 1)
// 	{
// 		print_message_philo(philo, "A -");
// 	}
// 	else if (philo->id_philo == 2)
// 	{
// 		usleep(1000);
// 		print_message_philo(philo, "B -");
// 	}
// 	else if (philo->id_philo == 3)
// 	{
// 		usleep(2000);
// 		print_message_philo(philo, "C -");
// 	}

// 	return (NULL);
// }

// void *routine(void *arg)
// {
// 	t_data		*data;
// 	t_philo		*philo;
// 	int			i;

// 	philo = (t_philo *)arg;
// 	data = (t_data *)philo->data;

// 	i = 0;
	
// 	//El hilo se queda bloqueado aqui
// 	pthread_mutex_lock(&data->init);
// 	pthread_mutex_unlock(&data->init);

	
// 	while (1)
// 	{
// 		if (philo->id_philo == 1)
// 		{
// 			if (i == philo->times_each_philosopher_must_eat)
// 			{
// 				data->is_dead = 1;
// 				print_message_philo(philo, "PHILO A HA MUERTO");
// 				break ;
// 			}
// 			print_message_philo(philo, "A -");
// 		}
// 		else if (philo->id_philo == 2)
// 		{
// 			usleep(1000);
// 			print_message_philo(philo, "B -");
// 		}
// 		else if (philo->id_philo == 3)
// 		{
// 			usleep(2000);
// 			print_message_philo(philo, "C -");
// 		}
// 		if (data->is_dead == 1)
// 			break ;
// 		i++;
// 	}
// 	return (NULL);
// }

void *routine(void *arg)
{
	t_data		*data;
	t_philo		*philo;
	int			i;

	philo = (t_philo *)arg;
	data = (t_data *)philo->data;

	i = 0;
	
	//El hilo se queda bloqueado aqui
	pthread_mutex_lock(&data->init);
	pthread_mutex_unlock(&data->init);

	
	while (1)
	{
		if (philo->id_philo == 1)
		{
			if (i == philo->times_each_philosopher_must_eat)
			{
				data->is_dead = 1;
				print_message_philo(philo, "PHILO A HA MUERTO");
				break ;
			}
			print_message_philo(philo, "A -");
		}
		else if (philo->id_philo == 2)
		{
			if (ft_sleep(1000, data) == 1)
				break ;
			print_message_philo(philo, "B -");
		}
		else if (philo->id_philo == 3)
		{
			if (ft_sleep(2000, data) == 1)
				break ;
			print_message_philo(philo, "C -");
		}
		if (data->is_dead == 1)
			break ;
		i++;
	}
	return (NULL);
}

//TODO: Hacer bucle infinito para imprimir los mensajes igual, pero en un tiempo especifico (valor de argv[2]). 
//TODO: Si se pasa ese tiempo, acaba el programa.

//caso prueba: ./philo 2 60 120 10 
// 