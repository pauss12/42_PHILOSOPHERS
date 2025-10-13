/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   values_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 17:08:49 by pmendez-          #+#    #+#             */
/*   Updated: 2025/10/12 17:09:05 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	ft_atol(char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

long	value_parsing(char *str)
{
	char	*line;
	char	*temp;
	int		result;

	temp = NULL;
	line = ft_strtrim(str, " ");
	if (line[0] == '+')
		temp = ft_strtrim(line + 1, " ");
	else
		temp = ft_strdup(line);
	free(line);
	result = ft_atol(temp);
	free(temp);
	return (result);
}
