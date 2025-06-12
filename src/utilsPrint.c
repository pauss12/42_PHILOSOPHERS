/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:14:37 by pmendez-          #+#    #+#             */
/*   Updated: 2025/06/12 20:47:43 by pmendez-         ###   ########.fr       */
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
	str = ft_strjoin_variadica(3, RED "Error\n" RESET, ": ", error_message);
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

void	print_and_free(t_data *data)
{
	print_error("Error creating philosopher thread");
	free_struct(data);
}
