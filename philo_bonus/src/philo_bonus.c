/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:16:53 by pmendez-          #+#    #+#             */
/*   Updated: 2025/10/12 17:08:29 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	show_error_good_usage(void)
{
	printf(RED "ERROR \n" RESET);
	printf("Usage: ./philo \n");
	printf(ORANGE "[number_of_philosophers]" RESET " ==> Number of forks \n");
	printf(ORANGE "[time_to_die]" RESET " ==> Time until he dies\n");
	printf(ORANGE "[time_to_eat]" RESET " ==> Time he has to eat\n");
	printf(ORANGE "[time_to_sleep]" RESET " ==> Time he has to sleep \n");
	printf(ORANGE "[must_eat] optional" \
	RESET "\n\n");
}

static void	print_and_exit(char *message)
{
	write(1, message, 30);
	exit(1);
}

void	free_pid_child(t_data *data)
{
	if (data->philos)
		free(data->philos);
	if (sem_close(data->sem_print) == -1)
		print_and_exit("Error /sem_print failed closing");
	if (sem_close(data->sem_init) == -1)
		print_and_exit("Error /sem_init failed closing");
	if (sem_close(data->sem_dead) == -1)
		print_and_exit("Error /sem_dead failed closing");
	if (sem_close(data->sem_eat) == -1)
		print_and_exit("Error /sem_eat failed closing");
	if (sem_close(data->sem_forks) == -1)
		print_and_exit("Error /sem_forks failed closing");
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
