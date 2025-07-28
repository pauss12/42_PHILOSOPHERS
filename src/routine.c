/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:16:09 by pmendez-          #+#    #+#             */
/*   Updated: 2025/07/28 17:10:06 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleeping(t_philo *philo)
{
	unsigned long	start_time;

	print_message_philo(philo, IS_SLEEPING);
	start_time = get_time();
	while (get_time() - start_time < philo->time_to_sleep)
	{
		pthread_mutex_lock(philo->dead);
		if (*(philo->is_dead) == 1)
		{
			pthread_mutex_unlock(philo->dead);
			return (1);
		}
		pthread_mutex_unlock(philo->dead);
		usleep(100);
	}
	return (0);
}

int	thinking(t_philo *philo)
{
	if (check_if_philo_dead(philo) == 1)
		return (1);
	print_message_philo(philo, IS_THINKING);
	return (0);
}

static int	eaten(t_philo *philo)
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

int	eating(t_philo *philo)
{
	if (check_if_philo_dead(philo) == 1)
		return (1);
	takeForks(philo);
	pthread_mutex_lock(philo->eat);
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->eat);
	print_message_philo(philo, IS_EATING);
	while (1)
	{
		if (check_if_philo_dead(philo) == 1)
		{
			releaseForks(philo);
			return (1);
		}
		if (get_time() - philo->last_meal >= philo->time_to_eat)
			break ;
		usleep(10);
	}
	releaseForks(philo);
	if (eaten(philo) == 1)
		return (1);
	return (0);
}

static void	only_one(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	print_message_philo(philo, TAKE_FORK);
	ft_sleep(philo, philo->time_to_die);
	pthread_mutex_unlock(philo->fork_left);
}

//caso prueba: ./philo 2 60 120 10 
