/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:03:49 by pmendez-          #+#    #+#             */
/*   Updated: 2025/10/12 19:08:48 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

void	wait_for_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			print_and_free(data, "Error joining philosophers thread");
		i++;
	}
}

static void	only_one(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(philo->fork_left);
	pthread_mutex_lock(philo->eat);
	time = get_time() - philo->start_time;
	print_message_philo(philo, TAKE_FORK);
	philo->time_to_die = philo->time_to_die + time;
	pthread_mutex_unlock(philo->eat);
	ft_sleep(philo, philo->time_to_die);
	pthread_mutex_unlock(philo->fork_left);
}

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->init);
	pthread_mutex_unlock(philo->init);
	while (1)
	{
		if (check_if_philo_dead(philo) == 1)
			return (NULL);
		if (philo->id_philo % 2 != 0)
			usleep(1);
		if (philo->nb_philos == 1)
		{
			only_one(philo);
			break ;
		}
		if (eating(philo) == 1)
			return (NULL);
		if (sleeping(philo) == 1)
			return (NULL);
		if (thinking(philo) == 1)
			return (NULL);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;

	data = (t_data){0};
	if (check_args(argc, argv) == 1)
		return (1);
	initialize_struct(&data, argv);
	initialize_philos(&data, argv);
	create_threads(&data);
	return (0);
}
