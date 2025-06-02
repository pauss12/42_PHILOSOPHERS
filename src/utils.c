/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:34:57 by paula             #+#    #+#             */
/*   Updated: 2025/06/02 20:36:35 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(char *error_message)
{
	char	*str;

	if (error_message == NULL)
		return ;
	str = ft_strjoin_variadica(3, RED "Error\n" RESET, ": ", error_message);
	if (str == NULL)
	{
		ft_printf(RED "Error\n" RESET);
		ft_printf("Memory allocation failed");
		return ;
	}
	ft_putendl_fd(str, 2);
	free(str);
}

void print_message_philo(t_philo *philo, char *message)
{
	size_t time;

	time = get_time() - philo->start_time;
	pthread_mutex_lock(&philo->data->print);
	printf("%lu %d %s\n", time, philo->id_philo, message);
	pthread_mutex_unlock(&philo->data->print);
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

int check_if_philo_dead(t_data *data)
{
	pthread_mutex_lock(&data->dead);
	if (data->is_dead == 1)
	{
		pthread_mutex_unlock(&data->dead);
		return (1);
	}
	pthread_mutex_unlock(&data->dead);
	return (0);
}