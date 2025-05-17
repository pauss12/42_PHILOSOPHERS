/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paulamendezsv@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:03:49 by pmendez-          #+#    #+#             */
/*   Updated: 2025/05/17 20:02:01 by paula            ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "philo.h"

int main(int argc, char **argv)
{
	t_data data;

    if (check_args(argc, argv) == 1)
		return (1);
	initialize_struct(&data, argv);
	initialize_philos(&data, argv);
	create_threads(&data);
	//free_struct(&data);
	ft_printf("MAIN HAS FINISHED\n");
    return (0);
}

