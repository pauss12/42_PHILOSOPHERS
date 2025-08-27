/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_memory_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:18:49 by pmendez-          #+#    #+#             */
/*   Updated: 2025/08/27 20:01:40 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	semaphore_initialization(t_data *data)
{
	data->sem_print = sem_open("/sem_print", O_CREAT, 0644, 1);
	if (data->sem_print == SEM_FAILED)
		print_and_free(data, "Semaphore /sem_print creation failed\n");
	data->sem_init = sem_open("/sem_init", O_CREAT, 0644, 1);
	if (data->sem_init == SEM_FAILED)
		print_and_free(data, "Semaphore /sem_init creation failed\n");
	data->sem_dead = sem_open("/sem_dead", O_CREAT, 0644, 1);
	if (data->sem_dead == SEM_FAILED)
		print_and_free(data, "Semaphore /sem_dead creation failed\n");
	data->sem_eat = sem_open("/sem_eat", O_CREAT, 0644, 1);
	if (data->sem_eat == SEM_FAILED)
		print_and_free(data, "Semaphore /sem_eat creation failed\n");
	data->sem_forks = sem_open("/sem_forks", O_CREAT, 0644, data->num_philos);
	if (data->sem_forks == SEM_FAILED)
		print_and_free(data, "Semaphore /sem_forks creation failed\n");
}

void	initialize_struct(t_data *data, char *argv[])
{
	data->is_dead = 0;
	data->num_philos = ft_atoi(argv[1]);
	data->philos = ft_calloc(data->num_philos, sizeof(t_philo));
	if (!data->philos)
		print_and_free(data, RED "ERROR \n" RESET "Malloc failed\n");
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->philos->is_dead = &data->is_dead;
	if (argv[5] != NULL)
		data->times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		data->times_each_philosopher_must_eat = -1;
}

void	free_semaphores(t_data *data)
{
	if (sem_unlink("/sem_print") == -1)
		print_and_free(data, RED "ERROR\n" RESET "/sem_print unlink failed\n");
	if (sem_unlink("/sem_init") == -1)
		print_and_free(data, RED "ERROR\n" RESET "/sem_init unlink failed\n");
	if (sem_unlink("/sem_dead") == -1)
		print_and_free(data, RED "ERROR\n" RESET "/sem_dead unlink failed\n");
	if (sem_unlink("/sem_eat") == -1)
		print_and_free(data, RED "ERROR\n" RESET "/sem_eat unlink failed\n");
	if (sem_unlink("/sem_forks") == -1)
		print_and_free(data, RED "ERROR\n" RESET "/sem_forks unlink failed\n");
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

static void kill_all_pids(t_data *data)
{
    int   i;
    int   status;
    pid_t pid;

    while ((pid = waitpid(-1, &status, 0)) > 0)
    {
        if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
        {
            for (i = 0; i < data->num_philos; i++)
                kill(data->philos[i].pid, SIGKILL);
        }
    }
}


void	free_struct(t_data *data)
{
	kill_all_pids(data);
	free_semaphores(data);
	if (data->philos)
		free(data->philos);
}

