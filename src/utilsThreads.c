/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsThreads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:11:45 by pmendez-          #+#    #+#             */
/*   Updated: 2025/07/05 19:27:06 by pmendez-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "philo.h"

static char *create_str(t_philo *philo, char *message, size_t time)
{
	char *str;

	str = NULL;
	if (ft_strcmp(message, HAS_DIED) == 0)
		str = ft_strjoin_variadica(RED BOLD "%lu : PHILO %d %s\n" RESET, time, philo->id_philo, message);
	else if (ft_strcmp(message, IS_EATING) == 0)
		str = ft_strjoin_variadica(GREEN "%lu: PHILO %d %s\n" RESET , time, philo->id_philo, message);
	else if (ft_strcmp(message, IS_SLEEPING) == 0)
		str = ft_strjoin_variadica(CYAN "%lu: PHILO %d %s\n" RESET , time, philo->id_philo, message);
	else if (ft_strcmp(message, IS_THINKING) == 0)
		str = ft_strjoin_variadica(BLUE "%lu: PHILO %d %s\n" RESET , time, philo->id_philo, message);
	else if (ft_strcmp(message, TAKEN_RIGHT_FORK) == 0)
		str = ft_strjoin_variadica(MAGENTA "%lu: PHILO %d %s\n" RESET , time, philo->id_philo, message);
	else if (ft_strcmp(message, TAKEN_LEFT_FORK) == 0)
		str = ft_strjoin_variadica(ORANGE "%lu: PHILO %d %s\n" RESET , time, philo->id_philo, message);
	else
		str = ft_strjoin_variadica("%lu: PHILO %d %s\n", time, philo->id_philo, message);
	return (str);
}

void print_message_philo(t_philo *philo, char *message)
{
	size_t	time;
	char	*str;

	if (philo == NULL || message == NULL)
		return;
	str = NULL;
	time = get_time() - philo->start_time;
	pthread_mutex_lock(philo->print);
	str = create_str(philo, message, time);
	if (str)
	{
		printf("%s", str);
		free(str);
	}
	pthread_mutex_unlock(philo->print);
}

// int	ft_sleep(t_philo *philo, unsigned long total_sleep)
// {
// 	unsigned long	current_time;

// 	current_time = get_time();
// 	printf("TOTAL SLEEP ==> %lu\n", total_sleep);
// 	while (get_time() - current_time < total_sleep)
// 	{
// 		pthread_mutex_lock(philo->dead);
// 		if (*(philo->is_dead) == 1)
// 		{
// 			pthread_mutex_unlock(philo->dead);
// 			return (1);
// 		}
// 		pthread_mutex_unlock(philo->dead);
// 		usleep(10);
// 	}
// 	return (0);
// }

int ft_sleep(t_philo *philo, unsigned long total_sleep)
{
	unsigned long	current;

	(void)philo;
	current = get_time();
	while (get_time() - current < total_sleep)
	{
		usleep(10);
	}
	return (0);
}

unsigned long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return ((time.tv_sec * 1000UL) + (time.tv_usec / 1000));
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