/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forkTreatment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 21:27:34 by pmendez-          #+#    #+#             */
/*   Updated: 2025/06/12 21:31:58 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void takeForks(t_philo *philo)
{
    //pthread_mutex_lock(philo->fork_left);
    print_message_philo(philo, TAKEN_LEFT_FORK);
    //pthread_mutex_lock(philo->fork_right);
    print_message_philo(philo, TAKEN_RIGHT_FORK);  
}

void releaseForks(t_philo *philo)
{
   print_message_philo(philo, RELEASE_FORKS);
    //pthread_mutex_unlock(philo->fork_left);
    //pthread_mutex_unlock(philo->fork_right);
}