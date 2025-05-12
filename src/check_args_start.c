/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_start.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paulamendezsv@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:03:40 by pmendez-          #+#    #+#             */
/*   Updated: 2025/05/12 12:45:36 by paula            ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "philo.h"

static void show_error_good_usage()
{
    printf(RED "ERROR \n" RESET);
    printf( "Usage: ./philo \n" ); 
    printf(ORANGE "[number_of_philosophers]" RESET " ==> Number of forks \n" );
    printf(ORANGE "[time_to_die]" RESET " ==> Time to eat since his last meal or simulation init \n");
    printf(ORANGE "[time_to_eat]" RESET " ==> Time he has to eat, in which forks are occupied \n");
    printf(ORANGE "[time_to_sleep]" RESET " ==> Time he has to sleep \n");
	printf(ORANGE "[number_of_times_each_philosopher_must_eat] optional" RESET " ==> Number of times each philosopher must eat \n\n");
}

int check_args(int argc, char **argv)
{
    int i;
    int j;
    
    i = 1;
    if (argc != 5 && argc != 6)
    {
        show_error_good_usage();
        return (1);
    }
    while (i < argc)
    {
        j = 0;
        while (argv[i][j] != '\0')
        {
            if (argv[i][j] < '0' || argv[i][j] > '9')
			{
                printf(RED "ERROR \n" RESET "Argument [%s] is not a number\n", argv[i]);
				return (1);
			}
			j++;
        }
        i++;
    }
	return (0);
}
