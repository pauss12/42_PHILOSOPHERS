/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createThreads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:37:26 by pmendez-          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/07/07 20:15:03 by pmendez-         ###   ########.fr       */
=======
/*   Updated: 2025/07/05 19:28:18 by pmendez-         ###   ########.fr       */
>>>>>>> refs/remotes/origin/main
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

<<<<<<< HEAD
// static int check_philo_dead(t_data *data)
=======
//TODO: Comprobar que el tiempo de muerte de cada filósofo no se ha superado
// static void check_time_dead(t_data *data)
>>>>>>> refs/remotes/origin/main
// {
// 	pthread_mutex_lock(&data->dead);
// 	if (data->is_dead == 1)
// 	{
// 		pthread_mutex_lock(&data->print);
// 		printf(RED BOLD "PHILO %d HAS DIED 💀\n" RESET, data->philo->id_philo);
// 		pthread_mutex_unlock(&data->print);
// 		// data->is_dead = 0; 
// 		pthread_mutex_unlock(&data->dead);
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&data->dead);
// 	return (0);
// }

<<<<<<< HEAD
//TODO: Comprobar que el tiempo de muerte de cada filósofo no se ha superado
// static int check_time_dead(t_data *data)
// {
//     unsigned long current;
//     int i;

//     i = 0;
//     pthread_mutex_lock(&data->dead);
//     while (i < data->num_philos)
//     {
// 		current = get_time();
//         if (current - data->philo[i].last_meal >= data->philo[i].time_to_die)
//         {
//             data->is_dead = 1;
			
// 			pthread_mutex_lock(&data->print);
// 			printf(RED BOLD "PHILO %d HAS DIED ID: %d 💀\n" RESET, data->philo[i].id_philo, i);
// 			pthread_mutex_unlock(&data->print);
			

//             pthread_mutex_unlock(&data->dead);
//             return (1);
//         }
// 		usleep(10);
//         i++;
//     }
//     pthread_mutex_unlock(&data->dead);
// 	return (0);
// }

=======
>>>>>>> refs/remotes/origin/main
static int check_time_dead(t_data *data)
{
    unsigned long current;
    int i;

    i = 0;
<<<<<<< HEAD
    pthread_mutex_lock(&data->dead);
    while (i < data->num_philos)
    {
		current = get_time();
=======
    current = get_time();
    pthread_mutex_lock(&data->dead);
    while (i < data->num_philos)
    {		
>>>>>>> refs/remotes/origin/main
        if (current - data->philo[i].last_meal >= data->philo[i].time_to_die)
        {
            data->is_dead = 1;
			pthread_mutex_unlock(&data->dead);
			print_message_philo(&data->philo[i] - 1, HAS_DIED);
            return (1);
        }
		// usleep(10);
        i++;
    }
    pthread_mutex_unlock(&data->dead);
	return (0) ;
}

// static void check_status(t_data *data)
// {
// 	while (1)
// 	{
// 		while (check_philos_eaten(data) == 0)
// 		{
// 			if (check_philo_dead(data) == 1)
// 				return ;
// 			if (check_time_dead(data) == 1)
// 			{
// 				pthread_mutex_lock(&data->print);
// 				printf(RED BOLD "PHILO %d HAS DIED 💀\n" RESET, data->philo->id_philo);
// 				pthread_mutex_unlock(&data->print);
// 				return ;
// 			}
// 			usleep(100);
// 		}
// 		pthread_mutex_lock(&data->print);
		
// 	}
// }

// static void check_status(t_data *data)
// {
// 	while (1)
// 	{
// 		while (check_philos_eaten(data) == 0)
// 		{
// 			// if (check_philo_dead(data) == 1)
// 			// 	return ;
// 			if (check_time_dead(data) == 1)
// 			{
// 				pthread_mutex_lock(&data->print);
// 				printf(RED BOLD "PHILO %d HAS DIED 💀\n" RESET, data->philo->id_philo);
// 				pthread_mutex_unlock(&data->print);
// 				return ;
// 			}
// 			usleep(100);
// 		}
// 		pthread_mutex_lock(&data->print);
		
// 	}
// }

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

static void check_status(t_data *data)
{
	//print_memory_add(data);
	while (1)
	{
		if (check_philos_eaten(data) == 1)
			break ;
<<<<<<< HEAD
		if (check_time_dead(data) == 1)
			break ;
=======
>>>>>>> refs/remotes/origin/main
		usleep(10);
		// printf("Checking status...\n");
	}
	if (data->is_dead == 1)
	{
		pthread_mutex_lock(&data->print);
		printf(RED BOLD "PHILO %d HAS DIED 💀\n" RESET, data->philo->id_philo);
		pthread_mutex_unlock(&data->print);
		return ;
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
	printf("SALEEEEE\n");
	wait_for_threads(data);
	printf("\nHa esperado a los philos\n");
}
