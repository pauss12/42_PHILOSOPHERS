/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 00:22:52 by pmendez-          #+#    #+#             */
/*   Updated: 2025/08/04 19:11:44 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/philo_bonus.h"

static void	*check_status(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_philos_eaten(data) == 1)
			break ;
		if (check_time_dead(data) == 1)
			break ;
		usleep(9);
	}
	return (NULL);
}

void	*philo_routine(t_data *data)
{
    sem_wait(data->sem_init);
    data->start_time = get_time();
    data->last_meal = get_time();
    
    if (pthread_create(&data->monitor, NULL, check_status, data) != 0)
		print_and_free(data, "Error creating monitor thread");
    
    sem_post(data->sem_init);
    
    

    return (NULL);
}