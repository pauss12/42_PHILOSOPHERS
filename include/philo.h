#ifndef PHILO_H
#define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define ORANGE "\001\033[38;5;208m\002"
# define RESET "\033[0m"

// src/philo.c

// src/check_args_start.c
void check_args(int argc, char **argv);

#endif