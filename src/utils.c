/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paulamendezsv@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:43:08 by paula             #+#    #+#             */
/*   Updated: 2025/06/06 13:46:03 by paula            ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "philo.h"

static size_t	total_length(int count, va_list args)
{
	size_t	length;
	int		i;

	length = 0;
	i = 0;
	while (i < count)
	{
		length += ft_strlen(va_arg(args, char *));
		i++;
	}
	return (length);
}

char	*ft_strjoin_variadica(int count, ...)
{
	char	*result;
	char	*str;
	va_list	args;
	size_t	total_len;
	size_t	index;

	va_start(args, count);
	index = 0;
	total_len = total_length(count, args);
	va_end(args);
	result = (char *)ft_calloc(total_len + 1, sizeof(char));
	if (!result)
		return (NULL);
	va_start(args, count);
	while ((int)index < count)
	{
		str = va_arg(args, char *);
		while (*str)
			result[index++] = *str++;
	}
	va_end(args);
	result[index] = '\0';
	return (result);
}

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
	ft_memset(ptr, 0, count * size);
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

void	*ft_memset(void *str, int c, size_t len)
{
	size_t		n;
	char		*p;

	p = (char *)str;
	n = 0;
	while (n < len)
	{
		p[n] = c;
		n++;
	}
	return (str);
}