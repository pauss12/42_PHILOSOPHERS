/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:15:02 by pmendez-          #+#    #+#             */
/*   Updated: 2025/06/24 19:47:05 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char *joinInt(char *result, int value)
{
	char	*str_value;
	char	*new_result;

	str_value = ft_itoa(value);
	if (str_value == NULL)
		return (NULL);
	if (result == NULL)
		result = str_value;
	else
	{
		new_result = ft_strjoin(result, str_value);
		free(result);
		free(str_value);
		result = new_result;
	}
	return (result);
}

static char *joinString(char *result, char *str)
{
	int		i;
	char	*new_result;

	i = 0;
	new_result = NULL;
	if (result == NULL)
	{
		result = ft_calloc(ft_strlen((char *)str), sizeof(char));
		if (result == NULL)
			return (NULL);
		while (str[i] != '\0')
		{
			result[i] = str[i];
			i++;
		}
	}
	else
	{
		new_result = ft_strjoin(result, str);
		free(result);
		result = new_result;
	}
	return (result);
}

static char *joinChar(char *result, char c)
{
	char	*str_char;
	char	*new_result;

	str_char = (char *)ft_calloc(2, sizeof(char));
	if (str_char == NULL)
		return (NULL);
	str_char[0] = c;
	str_char[1] = '\0';
	if (result == NULL)
		result = str_char;
	else
	{
		new_result = ft_strjoin(result, str_char);
		free(result);
		free(str_char);
		result = new_result;
	}
	return (result);
}

char	*ft_strjoin_variadica(char *index, ...)
{
	char	*result;
	va_list	args;

	result = NULL;
	va_start(args, index);
	while (*index)
	{
		if (*index == '%')
		{
			index++;
			if (*index == 'd' || *index == 'i')
				result = joinInt(result, va_arg(args, int));
			else if (*index == 's')
				result = joinString(result, va_arg(args, char *));
			else if (*index == 'c')
				result = joinChar(result, (char )va_arg(args, int));
			else if (*index == 'l' && *(index + 1) == 'u')
				result = joinLong(result, va_arg(args, unsigned long));
		}
		else
			result = joinChar(result, *index);
		index++;
	}
	va_end(args);
	return (result);
}
