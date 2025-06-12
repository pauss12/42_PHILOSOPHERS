/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:16:09 by pmendez-          #+#    #+#             */
/*   Updated: 2025/06/12 21:35:00 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleeping(t_philo *philo)
{
	long start_time;

	start_time = get_time();
	while (get_time() - start_time < philo->time_to_sleep)
	{
		if (philo->is_dead == 1)
			return (NULL);
		usleep(100);
	}
	return (0);
}

int thinking(t_philo *philo)
{
	return (0);
}

static int eaten(t_philo *philo)
{
	pthread_mutex_lock(philo->eat);
	if (philo->times_each_philosopher_must_eat != -1)
	{
		philo->times_each_philosopher_must_eat--;
		if (philo->times_each_philosopher_must_eat == 0)
		{
			*philo->meals += 1;
			pthread_mutex_unlock(philo->eat);
			return (1);
		}
	}
	pthread_mutex_unlock(philo->eat);
	return (0);
}

int eating(t_philo *philo)
{
	if (check_if_philo_dead(philo) == 1)
		return (1);
	takeForks(philo);
	releaseForks(philo);
	if (eaten(philo) == 1)
		return (1);
	return (0);
}

void *routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->init);
	pthread_mutex_unlock(philo->init);
	while (check_if_philo_dead(philo) == 0)
	{
		if (eating(philo) == 1)
			return (NULL);
		if (thinking(philo) == 1)
			return (NULL);
		if (sleeping(philo) == 1)
			return (NULL);
	}
	return (NULL);
}

//caso prueba: ./philo 2 60 120 10 
