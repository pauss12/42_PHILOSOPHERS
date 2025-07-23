/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forkTreatment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 21:27:34 by pmendez-          #+#    #+#             */
/*   Updated: 2025/07/23 19:24:07 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void takeForks(t_philo *philo)
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

void releaseForks(t_philo *philo)
{
    if (philo->id_philo % 2 == 0)
    {
        pthread_mutex_unlock(philo->fork_left);
        pthread_mutex_unlock(philo->fork_right);
       // print_message_philo(philo, RELEASE_FORKS);
    }
    else
    {
        pthread_mutex_unlock(philo->fork_right);
        pthread_mutex_unlock(philo->fork_left);
        //print_message_philo(philo, RELEASE_FORKS);
    }
}
