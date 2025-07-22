/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forkTreatment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 21:27:34 by pmendez-          #+#    #+#             */
/*   Updated: 2025/07/22 21:22:13 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void takeForks(t_philo *philo)
// {
//     if (philo->id_philo % 2 != 0 && philo->nb_philos % 2 == 0)
//     {
//         pthread_mutex_lock(philo->fork_right);
//         print_message_philo(philo, TAKEN_RIGHT_FORK);  
//         pthread_mutex_lock(philo->fork_left);
//         print_message_philo(philo, TAKEN_LEFT_FORK);
//     }
//     else
//     {
//         pthread_mutex_lock(philo->fork_left);
        
//         print_message_philo(philo, TAKEN_LEFT_FORK);
//         pthread_mutex_lock(philo->fork_right);
//         print_message_philo(philo, TAKEN_RIGHT_FORK);
//     }
// }

void takeForks(t_philo *philo)
{
    if (philo->id_philo % 2 == 0)
    {
        pthread_mutex_lock(philo->fork_right);
        print_message_philo(philo, TAKEN_RIGHT_FORK);

        pthread_mutex_lock(philo->eat);
        *(philo->takenFork[1]) = 1;
        if (*(philo->takenFork[0]) == 0)
        {
            pthread_mutex_unlock(philo->eat);
            pthread_mutex_lock(philo->fork_left);
            print_message_philo(philo, TAKEN_LEFT_FORK);
            
            pthread_mutex_lock(philo->eat);
            *(philo->takenFork[0]) = 1;
            pthread_mutex_unlock(philo->eat);
        }
        else
        {
            *(philo->takenFork[1]) = 0;
            pthread_mutex_unlock(philo->eat);
            pthread_mutex_unlock(philo->fork_right);
            print_message_philo(philo, "SUELTA EL DERECHO");
        }
    }
    else
    {
        pthread_mutex_lock(philo->fork_left);
        print_message_philo(philo, TAKEN_LEFT_FORK);

        pthread_mutex_lock(philo->eat);
        *(philo->takenFork[0]) = 1;

        if (*(philo->takenFork[1]) == 0)
        {
            pthread_mutex_unlock(philo->eat);
            pthread_mutex_lock(philo->fork_right);
            print_message_philo(philo, TAKEN_RIGHT_FORK);

            pthread_mutex_lock(philo->eat);
            *(philo->takenFork[1]) = 1;
            pthread_mutex_unlock(philo->eat);
        }
        else
        {
            *(philo->takenFork[0]) = 0;
            pthread_mutex_unlock(philo->eat);
            pthread_mutex_unlock(philo->fork_left);
            print_message_philo(philo, "SUELTA EL IZQUIERDO");
        }
    }
}

// static void print_message_taking_forks(t_philo *philo, int right_fork_first, int first_try)
// {
//     if (right_fork_first == 1)
//     {
//         if (first_try == 1)
//             print_message_philo(philo, TAKEN_RIGHT_FORK);
//         else
//             print_message_philo(philo, TAKEN_LEFT_FORK);
//     }
//     else
//     {
//         if (first_try == 1)
//             print_message_philo(philo, TAKEN_LEFT_FORK);
//         else
//             print_message_philo(philo, TAKEN_RIGHT_FORK);
//     }
// }

// void takeForks(t_philo *philo)
// {
//     pthread_mutex_t *first_fork;
//     pthread_mutex_t *second_fork;
//     int right_fork_first;

//     right_fork_first = 0;
//     if (philo->id_philo % 2 != 0)
//     {
//         first_fork = philo->fork_right;
//         second_fork = philo->fork_left;
//         right_fork_first = 1;
//     }
//     else
//     {
//         first_fork = philo->fork_left;
//         second_fork = philo->fork_right;
//         right_fork_first = 0;
//     }
//     pthread_mutex_lock(first_fork);
//     print_message_taking_forks(philo, right_fork_first, 1);
//     pthread_mutex_lock(second_fork);
//     print_message_taking_forks(philo, right_fork_first, 0);
// }


// void releaseForks(t_philo *philo)
// {
//     if (philo->id_philo % 2 != 0 && philo->nb_philos % 2 == 0)
//     {
//         pthread_mutex_unlock(philo->fork_left);
//         pthread_mutex_unlock(philo->fork_right);
//         print_message_philo(philo, RELEASE_FORKS);
//     }
//     else
//     {
//         pthread_mutex_unlock(philo->fork_right);
//         pthread_mutex_unlock(philo->fork_left);
//         print_message_philo(philo, RELEASE_FORKS);
//     }
// }

// void releaseForks(t_philo *philo)
// {
//     if (philo->id_philo % 2 == 0)
//     {
//         pthread_mutex_unlock(philo->fork_left);
//         pthread_mutex_unlock(philo->fork_right);
//         print_message_philo(philo, RELEASE_FORKS);
//     }
//     else
//     {
//         pthread_mutex_unlock(philo->fork_right);
//         pthread_mutex_unlock(philo->fork_left);
//         print_message_philo(philo, RELEASE_FORKS);
//     }
// }

void releaseForks(t_philo *philo)
{
    pthread_mutex_lock(philo->eat);

    *(philo->takenFork[0]) = 0;
    *(philo->takenFork[1]) = 0;

    pthread_mutex_unlock(philo->eat);

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

    print_message_philo(philo, RELEASE_FORKS);
}
