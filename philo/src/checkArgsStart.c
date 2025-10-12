/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkArgsStart.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:03:40 by pmendez-          #+#    #+#             */
/*   Updated: 2025/10/12 13:50:46 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

static int	check_first_character(char *line, int i, char **temp)
{
	char	*aux;
	char	**str;

	aux = NULL;
	str = NULL;
	aux = ft_strtrim(line, " ");
	if (aux[0] == '\0')
	{
		*str = ft_strjoin("Valor no válido en posicion ", ft_itoa(i));
		print_error(*str);
		free(*str);
		free(aux);
		return (1);
	}
	if (aux[0] == '+')
		*temp = ft_strtrim(aux + 1, " ");
	else
		*temp = ft_strdup(aux);
	free(aux);
	return (0);
}

static int	check(int argc, int i, int j, char *argv[])
{
	char	*temp;

	temp = NULL;
	while (i < argc)
	{
		j = 0;
		if (check_first_character(argv[i], i, &temp) == 1)
			return (1);
		while (temp[j] != '\0')
		{
			if (temp[0] == '+')
				temp = ft_strtrim(temp + 1, " ");
			if (temp[j] < '0' || temp[j] > '9')
			{
				print_error("Arguments must be digits");
				free(temp);
				return (1);
			}
			j++;
		}
		free(temp);
		i++;
	}
	return (0);
}

int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if ((argc != 5 && argc != 6))
	{
		show_error_good_usage();
		return (1);
	}
	if (argv[i] != NULL && ft_atoi(argv[i]) == 0)
	{
		print_error("The program needs at least one philosopher");
		return (1);
	}
	if (argv[i] != NULL && ft_atoi(argv[i]) > 200)
	{
		print_error("There are too many philos");
		return (1);
	}
	if (check(argc, i, j, argv) == 1)
		return (1);
	return (0);
}
