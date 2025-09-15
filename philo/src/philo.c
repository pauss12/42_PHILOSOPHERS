/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:03:49 by pmendez-          #+#    #+#             */
/*   Updated: 2025/09/15 21:01:31 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	pthread_mutex_lock(philo->fork_left);
	print_message_philo(philo, TAKE_FORK);
	ft_sleep(philo->time_to_die);
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
