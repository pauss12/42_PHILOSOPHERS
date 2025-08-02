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

}   t_philo;


typedef struct s_data
{

}   t_data;

void	free_struct(t_data *data);
void	initialize_struct(t_data *data, char *argv[]);

#endif