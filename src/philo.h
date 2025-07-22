/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:04:41 by pmendez-          #+#    #+#             */
/*   Updated: 2025/07/22 18:46:45 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <limits.h>
# include <sys/time.h>
# include <stdint.h>
# include <fcntl.h>
# include <string.h>
# include <stdarg.h>

# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define ORANGE "\001\033[38;5;208m\002"
# define RESET "\033[0m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define BOLD "\033[1m"

# define TAKEN_RIGHT_FORK    "has taken right fork 🍴"
# define TAKEN_LEFT_FORK     "has taken left fork 🍴"
# define IS_EATING           " is eating 🍝"
# define IS_SLEEPING         " is sleeping 😴"
# define IS_THINKING         "is thinking 🤔 "
# define HAS_DIED            "is dead 💀"
# define RELEASE_FORKS "has released forks"

typedef struct s_philo
{
	int				id_philo;
	int				nb_philos;
	unsigned long			start_time;
	unsigned long			last_meal;
	unsigned long			time_to_eat;
	unsigned long			time_to_die;
	unsigned long			time_to_sleep;
	int			    *meals;
	int				times_each_philosopher_must_eat;
	pthread_mutex_t	*print;
	pthread_mutex_t	*init;
	pthread_mutex_t	*dead;
	pthread_mutex_t	*eat;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*fork_left;
	int				*is_dead;
	pthread_t		thread;

}	t_philo;

// time_to_die ==> El tiempo que un filósofo puede estar sin comer antes de morir; es el contador final
// al que se le suma el tiempo de la última comida.

// ms_to_die_argv ==> Tiempo de muerte pasado como argumento. NO SE ACTUALIZA

typedef struct s_data
{
	int				num_philos;
	int				is_dead;
	int				meals;
	t_philo			*philo;
	pthread_mutex_t	print;
	pthread_mutex_t	init;
	pthread_mutex_t	dead;
	pthread_mutex_t	eat;
	pthread_mutex_t	*forks;

}	t_data;

// #############################################################################
// ############################# CHECK_ARGS_START ##############################
// #############################################################################
int		check_args(int argc, char **argv);

// #############################################################################
// ############################# UTILS_THREADS.C ###############################
// #############################################################################
void	print_message_philo(t_philo *philo, char *message);
int		ft_sleep(t_philo *philo, unsigned long total_sleep);
unsigned long	get_time(void);
int		check_if_philo_dead(t_philo *philo);

// #############################################################################
// ############################# TREAT_MEMORY ##################################
// #############################################################################
void	initialize_struct(t_data *data, char *argv[]);
void	initialize_philos(t_data *data, char *argv[]);
void	free_struct(t_data *data);

// #############################################################################
// ############################# RUTINAS #######################################
// #############################################################################
void	*routine(void *arg);
int		eating(t_philo *philo);
int 	thinking(t_philo *philo);
int		sleeping(t_philo *philo);

// ##############################################################################
// ############################# CREATE_THREADS ################################
// #############################################################################
void	create_threads(t_data *data);

// ##############################################################################
// ############################# UTILS ##########################################
// ##############################################################################
char	*ft_strjoin_variadica(char *index, ...);
void	*ft_calloc(size_t count, size_t size);
int		ft_atoi(const char *str);
void	*ft_memset(void *str, int c, size_t len);

// ##############################################################################
// ############################# UTILS2 ########################################
// ##############################################################################
int		ft_strlen(char *str);
int		ft_strcmp(const char *s1, const char *s2);

// ##############################################################################
// ############################# ITOA_JOIN_LONG #################################
// ##############################################################################
char	*ft_itoa(int value);
char	*joinLong(char *result, unsigned long value, char **index);


// ##############################################################################
// ############################# UTILS_PRINT ####################################
// ##############################################################################
void	print_error(char *error_message);
void	ft_putendl_fd(char *s, int fd);
void	print_and_free(t_data *data, char *message);
char	*ft_strjoin(char *s1, char *s2);

// ##############################################################################
// ############################# FORK TREATMENT #################################
// ##############################################################################
void	takeForks(t_philo *philo);
void	releaseForks(t_philo *philo);

// philo.c
void wait_for_threads(t_data *data);

#endif
