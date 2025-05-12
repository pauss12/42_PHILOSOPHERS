/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paulamendezsv@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:04:41 by pmendez-          #+#    #+#             */
/*   Updated: 2025/05/12 13:43:10 by paula            ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include "../libft/libft.h"

# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define ORANGE "\001\033[38;5;208m\002"
# define RESET "\033[0m"

typedef struct s_philo
{
	int				id_philo;
	int				times_eaten;
	int				is_dead;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_each_philosopher_must_eat;
	pthread_mutex_t	*fork;

}	t_philo;

typedef struct s_data
{
	int				num_philos;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	int				loop_finished;

}	t_data;

// #############################################################################
// ############################# CHECK_ARGS_START ##############################
// #############################################################################
int		check_args(int argc, char **argv);

// #############################################################################
// ############################# TREAT_MEMORY ##################################
// #############################################################################
void	initialize_struct(t_data *data);
void	initialize_philos(t_data *data, char *argv[]);

// #############################################################################
// ############################# RUTINAS #######################################
// #############################################################################
void	*sleeping(t_data *data);
void	*eating(t_data *data);
void	*thinking(t_data *data);

#endif
