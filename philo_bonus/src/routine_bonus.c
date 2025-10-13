/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:18:30 by pmendez-          #+#    #+#             */
/*   Updated: 2025/10/12 19:14:17 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static int	eating(t_data *data)
{
	long	last_meal;

	sem_wait(data->sem_dead);
	sem_post(data->sem_dead);
	take_and_release_forks(data, 0);
	sem_wait(data->sem_eat);
	data->last_meal = get_time();
	last_meal = data->last_meal;
	print_message_philo(data, IS_EATING);
	sem_post(data->sem_eat);
	while (1)
	{
		if (get_time() - last_meal >= data->time_to_eat)
			break ;
		usleep(10);
	}
	take_and_release_forks(data, 1);
	sem_wait(data->sem_init);
	if (check_meals(data) == 1)
	{
		sem_post(data->sem_init);
		return (1);
	}
	sem_post(data->sem_init);
	return (0);
}

static int	thinking(t_data *data)
{
	sem_wait(data->sem_dead);
	sem_post(data->sem_dead);
	print_message_philo(data, IS_THINKING);
	return (0);
}

static int	sleeping(t_data *data)
{
	long	start;

	sem_wait(data->sem_dead);
	sem_post(data->sem_dead);
	start = get_time();
	print_message_philo(data, IS_SLEEPING);
	while (1)
	{
		sem_wait(data->sem_dead);
		sem_post(data->sem_dead);
		if (get_time() - start >= data->time_to_sleep)
			break ;
		usleep(10);
	}
	return (0);
}

static int	only_one(t_data *data)
{
	long	time;

	if (data->num_philos == 1)
	{
		sem_wait(data->sem_eat);
		time = get_time() - data->start_time;
		data->time_to_die = data->time_to_die + time;
		sem_post(data->sem_eat);
		take_and_release_forks(data, 0);
		return (1);
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
		if (only_one(data) == 1)
			break ;
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
	return (NULL);
}
