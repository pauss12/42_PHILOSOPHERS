/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:15:51 by pmendez-          #+#    #+#             */
/*   Updated: 2025/10/12 18:53:22 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static int	check_if_null(char *line, int i, char **str)
{
	int		j;

	j = 0;
	if (line[0] == '\0')
	{
		*str = ft_strjoin("Not a valid value in position ", ft_itoa(i));
		if (str == NULL)
			return (1);
		print_error(*str);
		free(*str);
		return (1);
	}
	while (line[j] != '\0')
	{
		if (line[j] != ' ' && line[j] != '+')
			break ;
		j++;
	}
	if (j == ft_strlen(line))
	{
		print_error("There cannot be a value with only spaces or symbols only");
		return (1);
	}
	return (0);
}

static int	check_first_character(char *line, int i, char **temp)
{
	char	*aux;
	char	*str;

	str = NULL;
	if (check_if_null(line, i, &str) == 1)
		return (1);
	aux = ft_strtrim(line, " ");
	if (aux[0] == '-')
	{
		print_error("There cannot be a negative value");
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
			if (temp[j] < '0' || temp[j] > '9')
			{
				if (temp[j] != '-')
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
