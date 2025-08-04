/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 00:32:47 by pmendez-          #+#    #+#             */
/*   Updated: 2025/08/04 19:06:50 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/philo_bonus.h"

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

// void	print_message_philo(t_philo *philo, char *message)
// {
// 	size_t	time;
// 	char	*str;

// 	if (philo == NULL || message == NULL)
// 		return ;
// 	str = NULL;
// 	time = get_time() - philo->start_time;
// 	if (check_if_philo_dead(philo) == 1)
// 		return ;
// 	sem_wait(data->print);
// 	str = create_str(philo, message, time);
// 	if (str)
// 	{
// 		printf("%s", str);
// 		free(str);
// 	}
// 	sem_post(philo->print);
// }

void	print_message_philo(t_data *data, char *message)
{
	size_t	time;
	char	*str;

	if (data == NULL || message == NULL)
		return ;
	str = NULL;
	time = get_time() - data->start_time;
	// if (check_if_philo_dead(philo) == 1)
	// 	return ;
	sem_wait(data->sem_print);
	str = create_str(data, message, time);
	if (str)
	{
		printf("%s", str);
		free(str);
	}
	sem_post(data->sem_print);
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

unsigned long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return ((time.tv_sec * 1000UL) + (time.tv_usec / 1000));
}