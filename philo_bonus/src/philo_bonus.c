/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 00:13:21 by pmendez-          #+#    #+#             */
/*   Updated: 2025/08/05 20:31:12 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/philo_bonus.h"

static void free_data_philo(t_data *data)
{
	if (data->philos)
		free(data->philos);
	if (sem_close(data->sem_forks) == -1)
		(write(2, "Error close sem_forks\n", 17));
	if (sem_close(data->sem_print) == -1)
		(write(2, "Error close sem_print\n", 18));
	if (sem_close(data->sem_init) == -1)
		(write(2, "Error close sem_init\n", 18));
	if (sem_close(data->sem_dead) == -1)
		(write(2, "Error close sem_dead\n", 17));
	if (sem_close(data->sem_eat) == -1)
		(write(2, "Error close sem_eat\n", 17));
}

void create_processes(t_data *data)
{
	int	i;

	i = 0;
	sem_wait(data->sem_init);
	while (i < data->num_philos)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid == 0)
		{
			data->philos[i].id_philo = i + 1;
			philo_routine(data);
			free_data_philo(data);
			exit(0);
		}
		else if (data->philos[i].pid < 0)
		{
			print_and_free(data, RED "ERROR \n" RESET "Fork failed\n");
			exit(1);
		}
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