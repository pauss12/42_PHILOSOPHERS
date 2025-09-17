/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:16:53 by pmendez-          #+#    #+#             */
/*   Updated: 2025/09/17 20:26:24 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void free_pid_child(t_data *data)
{
	if (data->philos)
		free(data->philos);
	if (sem_close(data->sem_print) == -1)
		print_and_free(data, RED "ERROR\n" RESET "/sem_print failed closing\n");
	if (sem_close(data->sem_init) == -1)
		print_and_free(data, RED "ERROR\n" RESET "/sem_init failed closing\n");
	if (sem_close(data->sem_dead) == -1)
		print_and_free(data, RED "ERROR\n" RESET "/sem_dead failed closing\n");
	if (sem_close(data->sem_eat) == -1)
		print_and_free(data, RED "ERROR\n" RESET "/sem_eat failed closing\n");
	if (sem_close(data->sem_forks) == -1)
		print_and_free(data, RED "ERROR\n" RESET "/sem_forks failed closing\n");
}

static void	create_processes(t_data *data)
{
	int	i;

	i = 0;
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
