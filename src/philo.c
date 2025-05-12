/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paulamendezsv@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:03:49 by pmendez-          #+#    #+#             */
/*   Updated: 2025/05/12 19:20:00 by paula            ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "philo.h"


int main(int argc, char **argv)
{
	t_data data;

    if (check_args(argc, argv) == 1)
		return (1);
	// initialize_struct(&data);
	// initialize_philos(&data, argv);
	create_threads(&data);
    return (0);
}

