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

int	sleeping(t_philo *philo)
{
	long start_time;

	print_message_philo(philo, IS_SLEEPING);
	pthread_mutex_lock(philo->dead);
	start_time = get_time();
	while (get_time() - start_time < philo->time_to_sleep)
	{
		if (*(philo->is_dead) == 1)
		{
			pthread_mutex_unlock(philo->dead);
			return (1);
		}
		usleep(9);
	}
	pthread_mutex_unlock(philo->dead);
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
	pthread_mutex_lock(philo->eat);
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->eat);
	print_message_philo(philo, IS_EATING);
	while (1)
	{
		if (check_if_philo_dead(philo) == 1)
        {
			pthread_mutex_lock(philo->print);
			printf("DEBUG: Died while eating loop.");
			pthread_mutex_unlock(philo->print);
			releaseForks(philo);
			return (1);
        }
		if (get_time() - philo->last_meal >= philo->time_to_eat)
			break ;
		usleep(9);
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

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->init);
	pthread_mutex_unlock(philo->init);

	if (philo->id_philo % 2 != 0)
		usleep(500);
	while (1)
	{
		if (check_if_philo_dead(philo) == 1)
		{
			pthread_mutex_lock(philo->print);
			printf("Pasa por aqui\n");
			pthread_mutex_unlock(philo->print);
			return (NULL);
		}
		if (philo->nb_philos == 1)
		{
			onlyOne(philo);
			break;
		}
		if (eating(philo) == 1)
		{
			pthread_mutex_lock(philo->print);
			printf("El valor de is_dead de PHILO %d es %d\n", philo->id_philo, *(philo->is_dead));
			pthread_mutex_unlock(philo->print);
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
