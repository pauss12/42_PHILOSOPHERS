/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:14:55 by pmendez-          #+#    #+#             */
/*   Updated: 2025/07/25 18:33:33 by pmendez-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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

int	ft_strlen(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
