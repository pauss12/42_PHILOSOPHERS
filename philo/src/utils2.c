/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:15:02 by pmendez-          #+#    #+#             */
/*   Updated: 2025/10/11 22:07:11 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static char	*first_part(char *color, size_t time, int id_philo)
{
	char	*temp1;
	char	*temp2;
	char	*aux;

	temp1 = join_long(color, time);
	if (temp1 == NULL)
		return (NULL);
	temp2 = ft_strjoin(temp1, " ");
	free(temp1);
	if (temp2 == NULL)
		return (NULL);
	aux = ft_itoa(id_philo);
	if (aux == NULL)
	{
		free(temp2);
		return (NULL);
	}
	temp1 = ft_strjoin(temp2, aux);
	free(temp2);
	free(aux);
	if (temp1 == NULL)
		return (NULL);
	return (temp1);
}

char	*join_strings(size_t time, char *msg, int id_philo, char *col)
{
	char	*temp1;
	char	*temp2;
	char	*aux;

	temp1 = NULL;
	temp2 = NULL;
	temp1 = first_part(col, time, id_philo);
	temp2 = ft_strjoin(temp1, " ");
	free(temp1);
	aux = ft_strjoin(temp2, msg);
	free(temp2);
	if (aux == NULL)
		return (NULL);
	temp2 = ft_strjoin(aux, RESET);
	free(aux);
	if (temp1 == NULL)
		return (NULL);
	temp1 = ft_strjoin(temp2, "\n");
	free(temp2);
	if (temp1 == NULL)
		return (NULL);
	return (temp1);
}

char	*ft_strtrim(char *s1, char *set)
{
	char	*ptr1;
	char	*result;
	int		cont;
	int		j;

	ptr1 = (char *)s1;
	result = NULL;
	j = 0;
	if (s1 != 0)
	{
		cont = 0;
		j = ft_strlen(ptr1);
		while (ptr1[cont] != '\0' && ft_strchr(set, ptr1[cont]))
			cont++;
		while ((j > cont) && ft_strchr(set, ptr1[j - 1]))
			j--;
		result = malloc(sizeof(char) * (j - cont + 1));
		if (result == NULL)
			return (NULL);
		if (result)
			ft_strlcpy(result, &ptr1[cont], j - cont + 1);
	}
	return (result);
}

size_t	ft_strlcpy(char *dest, char *src, size_t dstsize)
{
	size_t	contador;
	size_t	tamsrc;

	contador = 0;
	if (dstsize == 0)
	{
		tamsrc = ft_strlen(src);
		return (tamsrc);
	}
	while (contador < dstsize - 1 && src[contador] != '\0')
	{
		dest[contador] = src[contador];
		contador++;
	}
	dest[contador] = '\0';
	tamsrc = 0;
	while (src[tamsrc] != '\0')
	{
		tamsrc++;
	}
	return (tamsrc);
}

char	*ft_strchr(char *s, int c)
{
	int	cont;

	cont = 0;
	while (s[cont] != '\0')
	{
		if (s[cont] == (char)c)
			return ((char *)s + cont);
		cont++;
	}
	if ((char)c == '\0' && (char)s[cont] == '\0')
		return ((char *)s + cont);
	return (NULL);
}
