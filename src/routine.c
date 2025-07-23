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
	unsigned long	start_time;
	unsigned long	time_to_sleep;
	int				is_dead;

	print_message_philo(philo, IS_SLEEPING);
	start_time = get_time();
	time_to_sleep = philo->time_to_sleep;
	while (get_time() - start_time < time_to_sleep)
	{
		pthread_mutex_lock(philo->dead);
		is_dead = *(philo->is_dead);
		pthread_mutex_unlock(philo->dead);
		if (is_dead == 1)
			return (1);
		usleep(10);
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
	unsigned long	last_meal;
	unsigned long	time_to_eat;

	if (check_if_philo_dead(philo) == 1)
        return (1);
	takeForks(philo);
	pthread_mutex_lock(philo->eat);
	philo->last_meal = get_time();
	last_meal = philo->last_meal;
	time_to_eat = philo->time_to_eat;
	pthread_mutex_unlock(philo->eat);
	print_message_philo(philo, IS_EATING);
	while (1)
	{
		if (check_if_philo_dead(philo) == 1)
        {
			releaseForks(philo);
			return (1);
        }
		if (get_time() - last_meal >= time_to_eat)
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
	print_message_philo(philo, TAKE_FORK);
	ft_sleep(philo, philo->time_to_die);
}

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->init);
	pthread_mutex_unlock(philo->init);

	// if (philo->id_philo % 2 != 0)
	// 	usleep(500);
	while (1)
	{
		if (check_if_philo_dead(philo) == 1)
			return (NULL);
		if (philo->nb_philos == 1)
		{
			onlyOne(philo);
			break;
		}
		if (philo->id_philo % 2 == 0)
			usleep(1);
		if (eating(philo) == 1)
			return (NULL);
		if (sleeping(philo) == 1)
			return (NULL);
		if (thinking(philo) == 1)
			return (NULL);
	}
	return (NULL);
}

//caso prueba: ./philo 2 60 120 10 
