/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paulamendezsv@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:16:09 by paula             #+#    #+#             */
/*   Updated: 2025/05/12 21:12:59 by paula            ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "philo.h"

int	sleeping(t_data *data)
{
	long start_time;

	start_time = get_time();
	while (get_time() - start_time < data->philo->time_to_sleep)
	{
		if (data->philo->is_dead == 1)
			return (NULL);
		usleep(100);
	}

}

void routine(t_data *data)
{
	//Esta muerto¿?
	if (data->is_dead == 1)
		return ;

	//Comer
	is_eating(data);

	//Dormir
	sleeping(data);

	//Pensar
	thinking(data);
}
