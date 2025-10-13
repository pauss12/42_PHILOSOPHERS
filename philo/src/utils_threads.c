/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:11:45 by pmendez-          #+#    #+#             */
/*   Updated: 2025/10/12 18:28:33 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static char	*create_str(t_philo *philo, char *message, size_t time)
{
	char	*str;
	int		id_philo;

	str = NULL;
	id_philo = philo->id_philo;
	if (ft_strcmp(message, IS_EATING) == 0)
		str = join_strings(time, message, id_philo, GREEN);
	else if (ft_strcmp(message, IS_SLEEPING) == 0)
		str = join_strings(time, message, id_philo, CYAN);
	else if (ft_strcmp(message, IS_THINKING) == 0)
		str = join_strings(time, message, id_philo, PURPLE);
	else if (ft_strcmp(message, TAKE_FORK) == 0)
		str = join_strings(time, message, id_philo, ORANGE);
	else
		str = join_strings(time, message, id_philo, RESET);
	return (str);
}

void	print_message_philo(t_philo *philo, char *message)
{
	size_t	time;
	char	*str;

	if (philo == NULL || message == NULL)
		return ;
	str = NULL;
	time = get_time() - philo->start_time;
	if (check_if_philo_dead(philo) == 1)
		return ;
	pthread_mutex_lock(philo->print);
	str = create_str(philo, message, time);
	if (str)
	{
		printf("%s", str);
		free(str);
	}
	pthread_mutex_unlock(philo->print);
}

int	ft_sleep(t_philo *philo, long total_sleep)
{
	long	current_time;

	current_time = get_time();
	while (get_time() - current_time < total_sleep)
	{
		pthread_mutex_lock(philo->dead);
		if (*(philo->is_dead) == 1)
		{
			pthread_mutex_unlock(philo->dead);
			return (1);
		}
		pthread_mutex_unlock(philo->dead);
		usleep(10);
	}
	return (0);
}

long	get_time(void)
{
	struct timeval	time;
	long			time_returned;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	time_returned = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (time_returned);
}

int	check_if_philo_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead);
	if (*(philo->is_dead) == 1)
	{
		pthread_mutex_unlock(philo->dead);
		return (1);
	}
	pthread_mutex_unlock(philo->dead);
	return (0);
}
