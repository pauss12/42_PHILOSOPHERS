/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsThreads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:11:45 by pmendez-          #+#    #+#             */
/*   Updated: 2025/06/13 21:27:26 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//printf(RED BOLD "%lu: PHILO %d %s\n" RESET , time, philo->id_philo, message);

void print_message_philo(t_philo *philo, char *message)
{
	size_t	time;
	char	*str;

	str = NULL;
	time = get_time() - philo->start_time;
	pthread_mutex_lock(philo->print);

	if (ft_strcmp(message, HAS_DIED) == 0)
		str = ft_strjoin_variadica(RED BOLD "%lu : PHILO %d %s\n" RESET, time, philo->id_philo, message);
	// else if (ft_strcmp(message, IS_EATING) == 0)
	// 	printf(GREEN "%lu: PHILO %d %s\n" RESET , time, philo->id_philo, message);
	// else if (ft_strcmp(message, IS_SLEEPING) == 0)
	// 	printf(CYAN "%lu: PHILO %d %s\n" RESET , time, philo->id_philo, message);
	// else if (ft_strcmp(message, IS_THINKING) == 0)
	// 	printf(BLUE "%lu: PHILO %d %s\n" RESET , time, philo->id_philo, message);
	// else if (ft_strcmp(message, TAKEN_RIGHT_FORK) == 0)
	// 	printf(MAGENTA "%lu: PHILO %d %s\n" RESET , time, philo->id_philo, message);
	// else if (ft_strcmp(message, TAKEN_LEFT_FORK) == 0)
	// 	printf(ORANGE "%lu: PHILO %d %s\n" RESET , time, philo->id_philo, message);
	// else
	// 	printf("%lu: PHILO %d %s\n", time, philo->id_philo, message);
	printf("%s\n", str);

	pthread_mutex_unlock(philo->print);
}


int	ft_sleep(int total_sleep, t_data *data)
{
	int current_time;
	current_time = get_time();

	while (get_time() - current_time < (unsigned long)total_sleep)
	{
		pthread_mutex_lock(&data->dead);
		if (data->is_dead == 1)
		{
			pthread_mutex_unlock(&data->dead);
			return (1);
		}
		pthread_mutex_unlock(&data->dead);
		usleep(10);
	}
	return (0);
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int check_if_philo_dead(t_philo *philo)
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