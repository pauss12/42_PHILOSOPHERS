/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paulamendezsv@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:42:58 by paula             #+#    #+#             */
/*   Updated: 2025/06/06 13:43:01 by paula            ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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