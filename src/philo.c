/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:03:49 by pmendez-          #+#    #+#             */
/*   Updated: 2025/07/23 20:07:01 by pmendez-         ###   ########.fr       */
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
