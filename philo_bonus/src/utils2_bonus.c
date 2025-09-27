/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:19:11 by pmendez-          #+#    #+#             */
/*   Updated: 2025/09/27 20:16:54 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"


// char	*join_strings(size_t time, char *msg, int id_philo, char *color)
// {
// 	char	*temp1;
// 	char	*temp2;
// 	char	*aux;

// 	temp1 = NULL;
// 	temp2 = NULL;
// 	temp1 = join_long(color, time);
// 	if (temp1 == NULL)
// 		return (NULL);
// 	temp2 = ft_strjoin(temp1, " ");
// 	free(temp1);
// 	if (temp2 == NULL)
// 		return (NULL);
// 	aux = ft_itoa(id_philo);
// 	if (aux == NULL)
// 	{
// 		free(temp2);
// 		return (NULL);
// 	}
// 	temp1 = ft_strjoin(temp2, aux);
//     free(temp2);
// 	free(aux);
// 	if (temp1 == NULL)
// 		return (NULL);
//  temp2 = ft_strjoin(temp1, " ");
//  free(temp1);
//  aux = ft_strjoin(temp2, msg);
//  free(temp2);
// 	if (aux == NULL)
// 		return (NULL);
// 	temp1 = ft_strjoin(aux, RESET);
// 	free(aux);
// 	if (temp1 == NULL)
// 		return (NULL);
// 	printf("cadena [%s]\n", temp1);
// 	return (NULL);
// }

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

char	*join_strings(size_t time, char *msg, int id_philo, char *color)
{
	char	*temp1;
	char	*temp2;
	char	*aux;

	temp1 = NULL;
	temp2 = NULL;
	temp1 =  first_part(color, time, id_philo);
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
