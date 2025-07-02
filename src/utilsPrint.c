/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsPrint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:14:37 by pmendez-          #+#    #+#             */
/*   Updated: 2025/07/02 20:50:10 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Imprime un mensaje de error en la salida estándar de error.
 * @param error_message: Mensaje de error a imprimir.
 * Si el mensaje es nulo, no se imprime nada.
 * Si la asignación de memoria falla, se imprime un mensaje de error genérico.
 * El mensaje se imprime en rojo y se precede por "Error: ".
 * * @example
 * print_error("Invalid argument");
 * Imprime: "Error: Invalid argument" en rojo.
 */
void	print_error(char *error_message)
{
	char	*str;

	if (error_message == NULL)
		return ;
	str = ft_strjoin_variadica(RED "Error\n" RESET, ": %s ", error_message);
	if (str == NULL)
	{
		printf(RED "Error\n" RESET);
		printf("Memory allocation failed");
		return ;
	}
	ft_putendl_fd(str, 2);
	free(str);
}

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	if (!s || fd < 0)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

void	print_and_free(t_data *data, char *message)
{
	print_error(message);
	free_struct(data);
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

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	char	*ptr1;
	char	*ptr2;
	size_t	i;
	size_t	j;

	ptr1 = (char *)s1;
	ptr2 = (char *)s2;
	i = 0;
	j = 0;
	str = malloc(((ft_strlen(ptr1) + ft_strlen(ptr2)) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
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
