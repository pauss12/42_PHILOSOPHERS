/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:20:52 by pmendez-          #+#    #+#             */
/*   Updated: 2025/10/04 22:48:38 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

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
	str = ft_strjoin(RED "Error\n" RESET, error_message);
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
	if (data->sem_print == SEM_FAILED)
		write(1, message, ft_strlen(message));
	else
		print_error(message);
	free_struct(data);
}

static char	*create_str(char *message, size_t time, int id_philo)
{
	char	*str;

	str = NULL;
	if (ft_strcmp(message, IS_EATING) == 0)
		str = join_strings(time, message, id_philo, GREEN);
	else if (ft_strcmp(message, IS_SLEEPING) == 0)
		str = join_strings(time, message, id_philo,CYAN);
	else if (ft_strcmp(message, IS_THINKING) == 0)
		str = join_strings(time, message, id_philo, PURPLE);
	else if (ft_strcmp(message, TAKE_FORK) == 0)
		str = join_strings(time, message, id_philo, ORANGE);
	else if (ft_strcmp(message, DIED) == 0)
		str = join_strings(time, message, id_philo, RED);
	else
		str = join_strings(time, message, id_philo, RESET);
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
	sem_wait(data->sem_dead);
	sem_post(data->sem_dead);
	sem_wait(data->sem_print);
	str = create_str(message, time, data->philos->id_philo);
	if (str)
	{
		printf("%s", str);
		free(str);
	}
	sem_post(data->sem_print);
}
