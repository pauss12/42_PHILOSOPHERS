/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 00:22:18 by pmendez-          #+#    #+#             */
/*   Updated: 2025/08/04 18:25:26 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/philo_bonus.h"

static void	show_error_good_usage(char *argv1)
{
	if (argv1 != NULL && ft_atoi(argv1) == 0)
	{
		print_error("The program needs at least one philosopher");
		return ;
	}
	if (argv1 != NULL && ft_atoi(argv1) >= 200)
	{
		print_error("There are too many philos");
		return ;
	}
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
	if ((argc != 5 && argc != 6) || ft_atoi(argv[1]) > 200)
	{
		show_error_good_usage(argv[1]);
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
