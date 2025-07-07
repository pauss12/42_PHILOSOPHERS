/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:03:49 by pmendez-          #+#    #+#             */
/*   Updated: 2025/07/07 20:09:18 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void wait_for_threads(t_data *data)
{
	int			i;

	i = 0;
	// printf("There are %d philos\n", data->num_philos);
	while (i < data->num_philos)
	{
		printf("Waiting for philosopher %d to finish\n", data->philo[i].id_philo);
		if (pthread_join(data->philo[i].thread, NULL) != 0)
		{
			pthread_mutex_lock(&data->print);
			print_error("Error joining philosopher thread");
			pthread_mutex_unlock(&data->print);
		}
		i++;
	}
}

int main(int argc, char **argv)
{
	t_data data;

	data = (t_data){0};
    if (check_args(argc, argv) == 1)
		return (1);
	initialize_struct(&data, argv);
	initialize_philos(&data, argv);
	create_threads(&data);
	free_struct(&data);
	printf("\n\nMAIN HAS FINISHED\n");

    return (0);
}

