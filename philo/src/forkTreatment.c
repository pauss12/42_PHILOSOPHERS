/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forkTreatment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 21:27:34 by pmendez-          #+#    #+#             */
/*   Updated: 2025/07/28 17:08:09 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	usleep(100);
	if (philo->id_philo % 2 == 0)
	{
		pthread_mutex_lock(philo->fork_right);
		print_message_philo(philo, TAKE_FORK);
		pthread_mutex_lock(philo->fork_left);
		print_message_philo(philo, TAKE_FORK);
	}
	else
	{
		pthread_mutex_lock(philo->fork_left);
		print_message_philo(philo, TAKE_FORK);
		pthread_mutex_lock(philo->fork_right);
		print_message_philo(philo, TAKE_FORK);
	}
}

void	release_forks(t_philo *philo)
{
	if (philo->id_philo % 2 == 0)
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
	}
	else
	{
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
	}
}
