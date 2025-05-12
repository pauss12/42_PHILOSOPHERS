/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paulamendezsv@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:34:57 by paula             #+#    #+#             */
/*   Updated: 2025/05/12 14:13:12 by paula            ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "philo.h"

void	print_message(t_data *data, int id_philo, char *message)
{
	pthread_mutex_lock(&data->forks[id_philo]);
	printf("%sPhilosopher %d %s%s\n", ORANGE, id_philo, message, RESET);
	pthread_mutex_unlock(&data->forks[id_philo]);
}

int has_died(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_philos)
	{
		if (data->philo[i].is_dead == 1)
			return (1);
		i++;
	}
	return (0);
}