/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_joinLong.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:14:48 by pmendez-          #+#    #+#             */
/*   Updated: 2025/10/11 21:38:03 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static char	*other(int len, int value)
{
	char	*str;

	str = (char *)ft_calloc((len + 1), sizeof(char));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	while (value != 0)
	{
		str[--len] = (value % 10) + '0';
		value = value / 10;
	}
	return (str);
}

char	*ft_itoa(int value)
{
	char	*str;
	int		temp;
	int		len;

	str = NULL;
	if (value >= 0 && value <= 9)
	{
		str = (char *)ft_calloc(2, sizeof(char));
		if (str == NULL)
			return (NULL);
		str[0] = value + '0';
		str[1] = '\0';
	}
	else
	{
		len = 0;
		temp = value;
		while (temp != 0)
		{
			temp = temp / 10;
			len++;
		}
		str = other(len, value);
	}
	return (str);
}

static int	get_ulong_digits(unsigned long n)
{
	int	count;

	if (n < 0)
		return (-1);
	if (n == 0)
		return (1);
	count = 0;
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static char	*ft_itoa_unsigned_long(unsigned long n)
{
	char	*str;
	int		len;

	len = get_ulong_digits(n);
	if (len < 0)
		return (NULL);
	str = (char *)ft_calloc(sizeof(char), (len + 1));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	if (n == 0)
	{
		str[0] = '0';
		return (str);
	}
	while (n > 0)
	{
		len--;
		str[len] = (n % 10) + '0';
		n = n / 10;
	}
	return (str);
}

char	*join_long(char *result, unsigned long value)
{
	char	*str_value;
	char	*new_result;

	str_value = ft_itoa_unsigned_long(value);
	if (str_value == NULL)
		return (NULL);
	if (result == NULL)
		result = str_value;
	else
	{
		new_result = ft_strjoin(result, str_value);
		free(str_value);
		result = new_result;
	}
	return (result);
}
