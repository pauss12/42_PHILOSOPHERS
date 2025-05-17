/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paulamendezsv@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:34:57 by paula             #+#    #+#             */
/*   Updated: 2025/05/17 18:25:23 by paula            ###   ########.fr       */
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
