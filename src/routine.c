/* *************************************************************************** */
/*                                                                             */
/*                                                        :::      ::::::::    */
/*   routine.c                                          :+:      :+:    :+:    */
/*                                                    +:+ +:+         +:+      */
/*   By: pmendez- <pmendez-@student.42madrid.com    +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+            */
/*   Created: 2025/05/12 13:16:09 by pmendez-          #+#    #+#              */
/*   Updated: 2025/07/07 20:13:40 by pmendez-         ###   ########.fr        */ 
/*                                                                			   */
/* *************************************************************************** */

# include "philo.h"

// int	sleeping(t_philo *philo)
// {
// 	long start_time;

// 	print_message_philo(philo, IS_SLEEPING);
// 	pthread_mutex_lock(philo->dead);
// 	start_time = get_time();
// 	while (get_time() - start_time < (unsigned long)philo->time_to_sleep)
// 	{
// 		if (*(philo->is_dead) == 1)
// 		{
// 			pthread_mutex_unlock(philo->dead);
// 			return (1);
// 		}
// 		usleep(100);
// 	}
// 	pthread_mutex_unlock(philo->dead);
// 	return (0);
// }


// MI 0 ==> es que ha ido bien
// MI 1 ==> es que ha ido mal

int	sleeping(t_philo *philo)
{
	long start_time;

	start_time = get_time();
	// printf("PHILO %d IS SLEEPING\n", philo->id_philo);
	print_message_philo(philo, IS_SLEEPING);
	while (1)
	{
		pthread_mutex_lock(philo->dead);
		if (*(philo->is_dead) == 1)
		{
			pthread_mutex_unlock(philo->dead);
			// print_message_philo(philo, "I AM DEAD");
			return (1);
		}
		pthread_mutex_unlock(philo->dead);
		if (get_time() - start_time >= philo->time_to_sleep)
			return (0);
		usleep(100);
	}
	return (0);
}

int thinking(t_philo *philo)
{
	if (check_if_philo_dead(philo) == 1)
		return (1);
	print_message_philo(philo, IS_THINKING);
	return (0);
}

static int eaten(t_philo *philo)
{
	pthread_mutex_lock(philo->dead);
	if (philo->times_each_philosopher_must_eat != -1)
	{
		philo->times_each_philosopher_must_eat--;
		if (philo->times_each_philosopher_must_eat == 0)
		{
			*philo->meals += 1;
			pthread_mutex_unlock(philo->dead);
			return (1);
		}
	}
	pthread_mutex_unlock(philo->dead);
	return (0);
}

int eating(t_philo *philo)
{
	if (check_if_philo_dead(philo) == 1)
        return (1);
	takeForks(philo);
	pthread_mutex_lock(philo->dead);
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->dead);
	print_message_philo(philo, IS_EATING);
	while (1)
	{
		//detecta la muerte del filósofo aqui
		if (check_if_philo_dead(philo) == 1)
        {
            print_message_philo(philo, "DEBUG: Died while eating loop.");
			releaseForks(philo);
			usleep(100);
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

static void onlyOne(t_philo *philo)
{
	print_message_philo(philo, TAKEN_LEFT_FORK);
	ft_sleep(philo, philo->time_to_die);
}

// void	*routine(void *arg)
// {
// 	t_philo		*philo;

// 	philo = (t_philo *)arg;
// 	pthread_mutex_lock(philo->init);
// 	pthread_mutex_unlock(philo->init);
// 	while (1)
// 	{
// 		if (philo->nb_philos == 1)
// 		{
// 			onlyOne(philo);
// 			return (NULL);
// 		}
// 		if (philo->id_philo % 2 == 0)
// 			usleep(1);
// 		if (eating(philo) == 1)
// 			return (NULL);
// 		if (sleeping(philo) == 1)
// 			return (NULL);
// 		if (thinking(philo) == 1)
// 			return (NULL);
// 	}
// 	return (NULL);
// }

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->init);
	pthread_mutex_unlock(philo->init);

	while (check_if_philo_dead(philo) == 0)
	{
		if (philo->nb_philos == 1)
		{
			onlyOne(philo);
			break;
		}
		if (philo->id_philo % 2 == 0)
			usleep(1);
		if (eating(philo) == 1)
		{
			// print_message_philo(philo, "sale de comer");
			return (NULL);
		}
		if (sleeping(philo) == 1)
			return (NULL);
		if (thinking(philo) == 1)
			return (NULL);
	}
	return (NULL);
}

//caso prueba: ./philo 2 60 120 10 
