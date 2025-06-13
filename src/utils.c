/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:14:55 by pmendez-          #+#    #+#             */
/*   Updated: 2025/06/13 21:21:24 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Asigna memoria dinámicamente y la inicializa a cero.
 * Asigna memoria dinámicamente para el número de elementos multiplicado 
 * por el tamaño de cada elemento.
 * Inicializa a cero el bloque de memoria asignado.
 * Retorna un puntero al bloque de memoria asignado.
 *
 * @param count: Número de elementos a asignar.
 * @param size: Tamaño de cada elemento.
 * @return: Puntero al bloque de memoria asignado, o nulo si la 
 * asignación falló.
 */

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count == 0 || size == 0)
		return (NULL);
	if (count > SIZE_MAX / size)
		return (NULL);
	ptr = (void *)malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	memset(ptr, 0, count * size);
	return (ptr);
}

/**
 * Convierte una cadena de caracteres a un número entero.
 * Ignora los espacios en blanco iniciales y los signos '+' o '-'.
 * Retorna el número entero correspondiente o 0 si la cadena no contiene 
 * ningún dígito.
 *
 * @param str: La cadena de caracteres a convertir.
 * @return: El número entero correspondiente a la cadena.
 */
int	ft_atoi(const char *str)
{
	int	i;
	int	num;
	int	negativo;

	i = 0;
	num = 0;
	negativo = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			negativo++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (negativo % 2 == 1)
		return (num * -1);
	return (num);
}


int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	if (s1 == NULL || s2 == NULL)
		return (1);
	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static char *other(int len, int value)
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

char *ft_itoa(int value)
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
			temp /= 10;
			len++;
		}
		str = other(len, value);
	}
	return (str);
}
