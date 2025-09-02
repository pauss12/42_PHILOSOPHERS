/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:18:30 by pmendez-          #+#    #+#             */
/*   Updated: 2025/09/02 21:59:03 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static int	eating(t_data *data)
{
	if (check_if_alive(data) == 1)
		return (1);
	take_and_release_forks(data, 0);
	sem_wait(data->sem_eat);
	data->last_meal = get_time();
	sem_post(data->sem_eat);
	print_message_philo(data, IS_EATING);
	while (1)
	{
		if (check_if_alive(data) == 1)
		{
			take_and_release_forks(data, 1);
			return (1);
		}
		if (get_time() - data->last_meal >= data->time_to_eat)
			break ;
		usleep(15);
	}
	take_and_release_forks(data, 1);
	sem_wait(data->sem_init);
	if (check_meals(data) == 1)
		return (1);
	sem_post(data->sem_init);
	return (0);
}

static int	thinking(t_data *data)
{
	if (check_if_alive(data) == 1)
		return (1);
	print_message_philo(data, IS_THINKING);
	return (0);
}

static int	sleeping(t_data *data)
{
	long	start;

	start = get_time();
	if (check_if_alive(data) == 1)
		return (1);
	print_message_philo(data, IS_SLEEPING);
	while (1)
	{
		if (check_if_alive(data) == 1)
			return (1);
		if (get_time() - start >= data->time_to_sleep)
			break ;
		usleep(10);
	}
	return (0);
}

void	*philo_routine(t_data *data)
{
	sem_wait(data->sem_init);
	data->last_meal = get_time();
	data->start_time = get_time();
	if (pthread_create(&data->monitor, NULL, check_status, data) != 0)
		print_and_free(data, "Error creating monitor thread");
	sem_post(data->sem_init);
	while (1)
	{
		if (data->num_philos == 1)
		{
			take_and_release_forks(data, 0);
			break ;
		}
		usleep(20);
		if (eating(data) == 1)
			break ;
		if (sleeping(data) == 1)
			break ;
		if (thinking(data) == 1)
			break ;
	}
	if (pthread_join(data->monitor, NULL) != 0)
		print_and_free(data, "Error joining the monitor");
	exit(1);
}
