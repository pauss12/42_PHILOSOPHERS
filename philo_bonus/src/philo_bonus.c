/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:16:53 by pmendez-          #+#    #+#             */
/*   Updated: 2025/10/09 00:25:48 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	free_pid_child(t_data *data)
{
	if (sem_close(data->sem_print) == -1)
	{
		write(1, "Error /sem_print failed closing", 30);
		exit(1);
	}
	if (sem_close(data->sem_init) == -1)
	{
		write(1, "Error /sem_init failed closing", 30);
		exit(1);
	}
	if (sem_close(data->sem_dead) == -1)
	{
		write(1, "Error /sem_dead failed closing", 30);
		exit(1);
	}
	if (sem_close(data->sem_eat) == -1)
	{
		write(1, "Error /sem_eat failed closing", 30);
		exit(1);
	}
	if (sem_close(data->sem_forks) == -1)
	{
		write(1, "Error /sem_forks failed closing", 30);
		exit(1);
	}
}

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
			free_pid_child(data);
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
