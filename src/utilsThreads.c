/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsThreads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:11:45 by pmendez-          #+#    #+#             */
/*   Updated: 2025/07/25 19:33:36 by pmendez-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "philo.h"

static char	*create_str(t_philo *philo, char *message, size_t time)
{
	char	*str;
	int		id_philo;

	str = NULL;
	id_philo = philo->id_philo;
	if (ft_strcmp(message, IS_EATING) == 0)
		str = join_variadica(GREEN"%lu %d %s\n"RESET, time, id_philo, message);
	else if (ft_strcmp(message, IS_SLEEPING) == 0)
		str = join_variadica(CYAN"%lu %d  %s\n"RESET, time, id_philo, message);
	else if (ft_strcmp(message, IS_THINKING) == 0)
		str = join_variadica(PURPLE"%lu %d %s\n"RESET, time, id_philo, message);
	else if (ft_strcmp(message, TAKE_FORK) == 0)
		str = join_variadica(ORANGE"%lu %d %s\n"RESET, time, id_philo, message);
	else
		str = join_variadica("%lu %d %s\n", time, id_philo, message);
	return (str);
}

// static char *create_str(t_philo *philo, char *message, size_t time)
// {
// 	char *str;

// 	str = NULL;
// 	if (ft_strcmp(message, IS_EATING) == 0)
// 		str = join_variadica("%lu %d %s\n", time, philo->id_philo, message);
// 	else if (ft_strcmp(message, IS_SLEEPING) == 0)
// 		str = join_variadica("%lu %d %s\n", time, philo->id_philo, message);
// 	else if (ft_strcmp(message, IS_THINKING) == 0)
// 		str = join_variadica("%lu %d %s\n", time, philo->id_philo, message);
// 	else if (ft_strcmp(message, TAKE_FORK) == 0)
// 		str = join_variadica("%lu %d %s\n", time, philo->id_philo, message);
// 	else
// 		str = join_variadica("%lu %d %s\n", time, philo->id_philo, message);
// 	return (str);
// }

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

int	ft_sleep(t_philo *philo, unsigned long total_sleep)
{
	unsigned long	current_time;

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

// int ft_sleep(t_philo *philo, unsigned long total_sleep)
// {
// 	unsigned long	current;

// 	(void)philo;
// 	current = get_time();
// 	while (get_time() - current < total_sleep)
// 	{
// 		usleep(10);
// 	}
// 	return (0);
// }

unsigned long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return ((time.tv_sec * 1000UL) + (time.tv_usec / 1000));
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
