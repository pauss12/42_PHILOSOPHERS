/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 00:22:52 by pmendez-          #+#    #+#             */
/*   Updated: 2025/08/07 19:40:01 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/philo_bonus.h"

static int	checking_time(t_data *data)
{
	unsigned long	last_meal;
	unsigned long	time_to_die;

	sem_wait(data->sem_eat);
	last_meal = data->last_meal;
	time_to_die = data->time_to_die;
	if (get_time() - last_meal > time_to_die)
	{
		print_message_philo(data, DIED);
		sem_wait(data->sem_dead);
		*data->philos->is_dead = 1;
		sem_post(data->sem_dead);
		sem_post(data->sem_eat);
		return (1);
	}
	sem_post(data->sem_eat);
	return (0);
}

static void	*check_status(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		sem_wait(data->sem_init);
		if (data->philos->times_each_philosopher_must_eat == 0)
		{
			sem_post(data->sem_init);
			return (NULL);
		}
		sem_post(data->sem_init);
		if (checking_time(data) == 1)
			break ;
		if (check_if_alive(data) == 1)
			break ;
		usleep(9);
	}
	return (NULL);
}

// static void only_one(t_data *data)
// {
// 	sem_wait(data->sem_forks);
// 	print_message_philo(data, TAKE_FORK);
// 	ft_sleep(data, data->time_to_die);
// 	sem_post(data->sem_forks);
// }

void	*philo_routine(t_data *data)
{
    sem_wait(data->sem_init);
    data->start_time = get_time();
    data->last_meal = get_time();
    if (pthread_create(&data->monitor, NULL, check_status, data) != 0)
		print_and_free(data, "Error creating monitor thread");
    sem_post(data->sem_init);

    // while (1)
	// {
	// 	if (data->num_philos == 1)
	// 	{
	// 		only_one(data);
	// 		if (pthread_join(data->monitor, NULL) != 0)
	// 			print_and_free(data, "Error joining monitor thread");
	// 		return (NULL);
	// 	}
	// }
    if (pthread_join(data->monitor, NULL) != 0)
		print_and_free(data, "Error joining monitor thread");
    return (NULL);
}

// void	*philo_routine(t_data *data)
// {
//     sem_wait(data->sem_init);
//     data->start_time = get_time();
//     data->last_meal = get_time();
//     if (pthread_create(&data->monitor, NULL, check_status, data) != 0)
// 		print_and_free(data, "Error creating monitor thread");
//     sem_post(data->sem_init);

//     while (1)
// 	{
// 		if (data->num_philos == 1)
// 		{
// 			only_one(data);
// 			break ;
// 		}
// 		if (eating(philo) == 1)
// 			return (NULL);
// 		if (sleeping(philo) == 1)
// 			return (NULL);
// 		if (thinking(philo) == 1)
// 			return (NULL);
// 	}
//     if (pthread_join(data->monitor, NULL) != 0)
// 		print_and_free(data, "Error joining monitor thread");
//     return (NULL);
// }