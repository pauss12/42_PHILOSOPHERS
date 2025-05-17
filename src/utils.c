/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paulamendezsv@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:34:57 by paula             #+#    #+#             */
/*   Updated: 2025/05/17 21:44:31 by paula            ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "philo.h"

void	print_error(char *error_message)
{
	char	*str;

	if (error_message == NULL)
		return ;
	str = ft_strjoin_variadica(3, RED "Error\n" RESET, ": ", error_message);
	if (str == NULL)
	{
		ft_printf(RED "Error\n" RESET);
		ft_printf("Memory allocation failed");
		return ;
	}
	ft_putendl_fd(str, 2);
	free(str);
}

void print_message(t_philo *philo, char *message)
{
	pthread_mutex_lock(&((t_data *)(philo->data))->print);
	ft_printf("%s%d %s%s\n", ORANGE, philo->id_philo, message, RESET);
	pthread_mutex_unlock(&((t_data *)(philo->data))->print);
}