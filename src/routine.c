/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paulamendezsv@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:16:09 by paula             #+#    #+#             */
/*   Updated: 2025/05/12 14:11:23 by paula            ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "philo.h"

void *sleeping(t_data *data)
{
	long start_time;

	start_time = get_time();

	//Mientras no haya muerto, duerme y no haya pasdo el tiempo de dormir
	while (!has_died())
}