/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 00:13:16 by pmendez-          #+#    #+#             */
/*   Updated: 2025/08/04 19:11:14 by pmendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

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
# include <semaphore.h>

# define GREEN "\033[0;32m"
# define RED "\033[0;31m\033[1m"
# define ORANGE "\001\033[38;5;208m\002"
# define RESET "\033[0m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"

# define TAKE_FORK    "has taken a fork 🍴"
# define IS_EATING           " is eating 🍝"
# define IS_SLEEPING         " is sleeping 😴"
# define IS_THINKING         "is thinking 🤔 "
# define DIED            "is dead 💀"
# define RELEASE_FORKS "has released forks"

typedef struct s_philo
{
	pid_t	pid;
	int		id_philo;
	int		times_each_philosopher_must_eat;
	int		*is_dead;

}   t_philo;


typedef struct s_data
{
	int				is_dead;
	int				num_philos;
	int				meals;
	unsigned long	last_meal;
	unsigned long	start_time;
	unsigned long	time_to_eat;
	unsigned long	time_to_die;
	unsigned long	time_to_sleep;
	t_philo			*philos;
	pthread_t		monitor;
	sem_t			*sem_print;
	sem_t			*sem_init;
	sem_t			*sem_dead;
	sem_t			*sem_eat;
	sem_t			*sem_forks;

}   t_data;

// #############################################################################
// ############################# CHECK_ARGS_START ##############################
// #############################################################################
int				check_args(int argc, char **argv);

// #############################################################################
// ############################# ITOA_JOIN_LONG ################################
// #############################################################################
char			*ft_itoa(int value);
char			*join_long(char *result, unsigned long value, char **index);

// #############################################################################
// ############################# TREAT_MEMORY ##################################
// #############################################################################
void			free_struct(t_data *data);
void			initialize_struct(t_data *data, char *argv[]);
void			semaphore_initialization(t_data *data);
void			free_semaphores(t_data *data);

// #############################################################################
// ########################### UTILS PRINT BONUS ###############################
// #############################################################################
void			print_error(char *error_message);
void			ft_putendl_fd(char *s, int fd);
void			print_and_free(t_data *data, char *message);
char			*ft_strjoin(char *s1, char *s2);
int				ft_atoi(const char *str);

// #############################################################################
// ############################# UTILS PHILO BONUS #############################
// #############################################################################
void			print_message_philo(t_philo *philo, char *message);
int				ft_sleep(t_philo *philo, unsigned long total_sleep);
unsigned long	get_time(void);

// #############################################################################
// ############################# UTILS #########################################
// #############################################################################
void			*ft_calloc(size_t count, size_t size);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strlen(char *str);

// #############################################################################
// ########################### UTILS2 BONUS ####################################
// #############################################################################
char			*join_variadica(char *index, ...);

// #############################################################################
// ############################# ROUTINE #######################################
// #############################################################################
void			*philo_routine(t_data *data);

// #############################################################################
// ############################# PHILO_BONUS ###################################
// #############################################################################
void			create_processes(t_data *data);

#endif