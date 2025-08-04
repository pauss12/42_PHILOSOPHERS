/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_memory_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 00:22:42 by pmendez-          #+#    #+#             */
/*   Updated: 2025/08/04 18:49:14 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/philo_bonus.h"

void semaphore_initialization(t_data *data)
{
	data->sem_print = sem_open("/sem_print", O_CREAT | O_EXCL, 0644, 1);
	if (data->sem_print == SEM_FAILED)
		print_and_free(data, RED "ERROR \n" RESET "Semaphore creation failed\n");
	data->sem_init = sem_open("/sem_init", O_CREAT | O_EXCL, 0644, 1);
	if (data->sem_init == SEM_FAILED)
		print_and_free(data, RED "ERROR \n" RESET "Semaphore creation failed\n");
	data->sem_dead = sem_open("/sem_dead", O_CREAT | O_EXCL, 0644, 1);
	if (data->sem_dead == SEM_FAILED)
		print_and_free(data, RED "ERROR \n" RESET "Semaphore creation failed\n");
	data->sem_eat = sem_open("/sem_eat", O_CREAT | O_EXCL, 0644, 1);
	if (data->sem_eat == SEM_FAILED)
		print_and_free(data, RED "ERROR \n" RESET "Semaphore creation failed\n");
	data->sem_forks = sem_open("/sem_forks", O_CREAT | O_EXCL, 0644, data->num_philos);
	if (data->sem_forks == SEM_FAILED)
		print_and_free(data, RED "ERROR \n" RESET "Semaphore creation failed\n");
}

void	initialize_struct(t_data *data, char *argv[])
{
	int	i;

	i = 0;
	data->is_dead = 0;
	data->num_philos = ft_atoi(argv[1]);
	data->philos = ft_calloc(data->num_philos, sizeof(t_philo));
	if (!data->philos)
		print_and_free(data, RED "ERROR \n" RESET "Malloc failed\n");
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->meals = 0;
	data->philos->is_dead = &data->is_dead;
	if (argv[5])
			data->philos[i].times_each_philosopher_must_eat = ft_atoi(argv[5]);
		else
			data->philos[i].times_each_philosopher_must_eat = -1;
}

void free_semaphores(t_data *data)
{
	if (sem_close(data->sem_print) == -1)
		print_and_free(data, RED "ERROR \n" RESET "Semaphore close failed\n");
	sem_close(data->sem_init);
	sem_close(data->sem_dead);
	sem_close(data->sem_eat);
	sem_close(data->sem_forks);
}

void	free_struct(t_data *data)
{
	
	free(data->philos);
	data->philos = NULL;
}