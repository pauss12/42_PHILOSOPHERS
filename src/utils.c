/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paulamendezsv@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:34:57 by paula             #+#    #+#             */
/*   Updated: 2025/05/12 21:03:52 by paula            ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "philo.h"

void	print_error(char *error_message)
{
	char	*str;

	if (cmd == NULL)
		return ;
	str = ft_strjoin_variadica(3, RED "Error\n" RESET, ": ", error_message);
	if (str == NULL)
	{
		ft_printf(RED "Error\n" END "Memory allocation failed");
		return ;
	}
	ft_putendl_fd(str, 2);
	free(str);
}

void	print_message(t_data *data, int id_philo, char *message)
{
	pthread_mutex_lock(data->print);
	
	pthread_mutex_unlock(data->print);
}