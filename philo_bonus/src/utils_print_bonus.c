/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 00:22:31 by pmendez-          #+#    #+#             */
/*   Updated: 2025/08/13 17:17:19 by pmendez-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

# include "../include/philo_bonus.h"

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
	str = join_variadica("%s Error%s \n %s ", RED, RESET, error_message);
	if (str == NULL)
	{
		printf(RED "Error\n" RESET);
		printf("Memory allocation failed");
		return ;
	}
	printf("%s\n", str);
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

static char	*create_str(char *message, size_t time, int id_philo)
{
	char	*str;

	str = NULL;
	if (ft_strcmp(message, IS_EATING) == 0)
		str = join_variadica(GREEN"%lu %d %s\n"RESET, time, id_philo, message);
	else if (ft_strcmp(message, IS_SLEEPING) == 0)
		str = join_variadica(CYAN"%lu %d  %s\n"RESET, time, id_philo, message);
	else if (ft_strcmp(message, IS_THINKING) == 0)
		str = join_variadica(PURPLE"%lu %d %s\n"RESET, time, id_philo, message);
	else if (ft_strcmp(message, TAKE_FORK) == 0)
		str = join_variadica(ORANGE"%lu %d %s\n"RESET, time, id_philo, message);
	else if (ft_strcmp(message, DIED) == 0)
		str = join_variadica(RED "%lu %d %s\n"RESET, time, id_philo, message);
	else
		str = join_variadica("%lu %d %s\n", time, id_philo, message);
	return (str);
}

void	print_message_philo(t_data *data, char *message)
{
	size_t	time;
	char	*str;

	if (data == NULL || message == NULL)
		return ;
	str = NULL;
	time = get_time() - data->start_time;
	if (check_if_alive(data) == 1)
		return ;
	sem_wait(data->sem_print);
	str = create_str(message, time, data->philos->id_philo);
	if (str)
	{
		printf("%s", str);
		free(str);
	}
	sem_post(data->sem_print);
}

