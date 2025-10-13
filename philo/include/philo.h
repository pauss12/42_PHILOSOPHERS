/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmendez- <pmendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:03:49 by pmendez-          #+#    #+#             */
/*   Updated: 2025/10/12 18:28:39 by pmendez-         ###   ########.fr       */
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
# define DIED            "died 💀"
# define RELEASE_FORKS "has released forks"

typedef struct s_philo
{
	int				id_philo;
	int				nb_philos;
	long			start_time;
	long			last_meal;
	long			time_to_eat;
	long			time_to_die;
	long			time_to_sleep;
	int				*meals;
	int				must_eat;
	pthread_mutex_t	*print;
	pthread_mutex_t	*init;
	pthread_mutex_t	*dead;
	pthread_mutex_t	*eat;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*fork_left;
	int				*is_dead;
	pthread_t		thread;

}	t_philo;

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
int				check_args(int argc, char **argv);

// #############################################################################
// ############################# UTILS_THREADS.C ###############################
// #############################################################################
long			get_time(void);
void			print_message_philo(t_philo *philo, char *message);
int				ft_sleep(t_philo *philo, long total_sleep);
int				check_if_philo_dead(t_philo *philo);

// #############################################################################
// ############################# TREAT_MEMORY ##################################
// #############################################################################
void			initialize_struct(t_data *data, char *argv[]);
void			initialize_philos(t_data *data, char *argv[]);
void			free_struct(t_data *data);

// #############################################################################
// ############################# RUTINAS #######################################
// #############################################################################
void			*routine(void *arg);
int				eating(t_philo *philo);
int				thinking(t_philo *philo);
int				sleeping(t_philo *philo);

// #############################################################################
// ############################# CREATE_THREADS ################################
// #############################################################################
void			create_threads(t_data *data);

// #############################################################################
// ############################# UTILS #########################################
// #############################################################################
void			*ft_calloc(size_t count, size_t size);
int				ft_atoi(const char *str);
void			*ft_memset(void *str, int c, size_t len);
char			*ft_strdup(const char *s1);

// #############################################################################
// ############################# UTILS2 ########################################
// #############################################################################
int				ft_strlen(char *str);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strtrim(char *s1, char *set);
size_t			ft_strlcpy(char *dest, char *src, size_t dstsize);
char			*ft_strchr(char *s, int c);
char			*join_strings(size_t time, char *msg, int id_philo, char *col);

// #############################################################################
// ############################# ITOA_JOIN_LONG ################################
// #############################################################################
char			*ft_itoa(int value);
char			*join_long(char *result, unsigned long value);

// #############################################################################
// ############################# UTILS_PRINT ###################################
// #############################################################################
void			print_error(char *error_message);
void			ft_putendl_fd(char *s, int fd);
void			print_and_free(t_data *data, char *message);
char			*ft_strjoin(char *s1, char *s2);

// #############################################################################
// ############################# FORK TREATMENT ################################
// #############################################################################
void			take_forks(t_philo *philo);
void			release_forks(t_philo *philo);

// #############################################################################
// ############################# PHILO  ########################################
// #############################################################################
void			wait_for_threads(t_data *data);
void			show_error_good_usage(void);

// #############################################################################
// ####################### VALUES PARSING  #####################################
// #############################################################################
long			ft_atol(char *str);
long			value_parsing(char *str);

#endif
