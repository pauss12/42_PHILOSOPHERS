/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkArgsStart.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:03:40 by pmendez-          #+#    #+#             */
/*   Updated: 2025/07/23 20:09:16 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	show_error_good_usage(void)
{
	printf(RED "ERROR \n" RESET);
	printf("Usage: ./philo \n");
	printf(ORANGE "[number_of_philosophers]" RESET " ==> Number of forks \n");
	printf(ORANGE "[time_to_die]" RESET " ==> Time until he dies\n");
	printf(ORANGE "[time_to_eat]" RESET " ==> Time he has to eat\n");
	printf(ORANGE "[time_to_sleep]" RESET " ==> Time he has to sleep \n");
	printf(ORANGE "[number_of_times_each_philosopher_must_eat] optional" \
	RESET "\n\n");
}

int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		show_error_good_usage();
		return (1);
	}
	if (ft_atoi(argv[1]) < 1)
	{
		print_error("The program needs at least one philosopher");
		return (1);
	}
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				print_error("Arguments must be digits");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
