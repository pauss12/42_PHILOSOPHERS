/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 00:32:47 by pmendez-          #+#    #+#             */
/*   Updated: 2025/08/17 16:23:07 by pmendez-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/philo_bonus.h"

int	ft_sleep(t_data *data, unsigned long total_sleep)
{
	unsigned long	current_time;

	current_time = get_time();
	while (get_time() - current_time < total_sleep)
	{
		sem_wait(data->sem_dead);
		if (data->is_dead == 1)
		{
			sem_post(data->sem_dead);
			return (1);
		}
		sem_post(data->sem_dead);
		usleep(10);
	}
	return (0);
}

unsigned long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return ((time.tv_sec * 1000UL) + (time.tv_usec / 1000));
}

int	check_if_alive(t_data *data)
{
	sem_wait(data->sem_dead);
	if (*data->philos->is_dead == 1)
	{
		sem_post(data->sem_dead);
		return (1);
	}
	sem_post(data->sem_dead);
	return (0);
}
