/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:21:05 by pmendez-          #+#    #+#             */
/*   Updated: 2025/10/04 23:00:05 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static int	checking_time(t_data *data)
{
	unsigned long	last_meal;
	unsigned long	time_to_die;

	sem_wait(data->sem_eat);
	last_meal = data->last_meal;
	time_to_die = data->time_to_die;
	if (get_time() - last_meal > time_to_die)
	{
		print_message_philo(data, DIED);
		sem_wait(data->sem_dead);
		sem_post(data->sem_eat);
		printf("antes del return 1\n");
		return (1);
	}
	sem_post(data->sem_eat);
	return (0);
}

void	*check_status(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		sem_wait(data->sem_init);
		if (data->times_each_philosopher_must_eat == 0)
		{
			sem_post(data->sem_init);
			return (NULL);
		}
		sem_post(data->sem_init);
		if (checking_time(data) == 1)
			break ;
		usleep(10);
	}
	exit(1);
}

void	take_and_release_forks(t_data *data, int released)
{
	if (released == 0)
	{
		usleep(50);
		sem_wait(data->sem_forks);
		print_message_philo(data, TAKE_FORK);
		sem_wait(data->sem_forks);
		print_message_philo(data, TAKE_FORK);
	}
	else
	{
		if (data->philos->id_philo % 2 == 0)
			usleep(50);
		sem_post(data->sem_forks);
		sem_post(data->sem_forks);
	}
}

int	check_meals(t_data *data)
{
	if (data->times_each_philosopher_must_eat > 0)
	{
		data->times_each_philosopher_must_eat--;
		if (data->times_each_philosopher_must_eat == 0)
		{
			ft_sleep(data->time_to_sleep / 2);
			sem_post(data->sem_init);
			return (1);
		}
	}
	return (0);
}
