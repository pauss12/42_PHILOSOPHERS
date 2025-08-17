/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 00:13:21 by pmendez-          #+#    #+#             */
/*   Updated: 2025/08/17 16:28:21 by pmendez-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/philo_bonus.h"

static void	create_processes(t_data *data)
{
	int	i;

	i = 0;
	sem_wait(data->sem_init);
	while (i < data->num_philos)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid == 0)
		{
			data->philos->id_philo = i + 1;
			philo_routine(data);
			exit(0);
		}
		else if (data->philos[i].pid < 0)
			print_and_free(data, RED "ERROR \n" RESET "Fork failed\n");
		i++;
	}
	sem_post(data->sem_init);
}

int	main(int argc, char **argv)
{
	t_data	data;

	data = (t_data){0};
	if (check_args(argc, argv) == 1)
		return (1);
	initialize_struct(&data, argv);
	semaphore_initialization(&data);
	create_processes(&data);
	free_struct(&data);
	return (0);
}
