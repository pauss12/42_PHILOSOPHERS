/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_are_all_capitalized.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 00:11:41 by pmendez-          #+#    #+#             */
/*   Updated: 2024/10/04 02:27:57 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * Comprueba si un caracter es una letra mayúscula.
 * 
 * @param c: el caracter a comprobar.
 * @return 1 si el caracter es una letra mayúscula, 0 en caso contrario.
 */

int	ft_isupper(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

int	ft_are_all_capitalized(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isupper(str[i]))
			return (0);
		i++;
	}
	return (1);
}
