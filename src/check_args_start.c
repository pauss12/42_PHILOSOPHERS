#include "../include/philo.h"

static void show_error_good_usage()
{
    printf(RED "ERROR \n\n" RESET);
    printf( "Usage: ./philo \n\n" ); 
    printf(ORANGE "[number_of_philosophers]" RESET " ==> Number of forks \n\n" );
    printf(ORANGE "[time_to_die]" RESET " ==> Time to eat since his last meal or simulation init \n\n");
    printf(ORANGE "[time_to_eat]" RESET " ==> Time he has to eat, in which forks are occupied \n\n");
    printf(ORANGE "[time_to_sleep]" RESET " ==> Time he has to sleep \n\n");
}

void check_args(int argc, char **argv)
{
    int i;
    int j;
    
    i = 1;
    if (argc != 5 && argc != 6)
    {
        show_error_good_usage();
        exit(1);
    }
    while (i < argc)
    {
        j = 0;
        while (argv[i][j] != '\0')
        {
            if (argv[i][j] < '0' || argv[i][j] > '9')
            {
                printf(RED "ERROR \n" RESET "Argument [%s] is not a number\n", argv[i]);
            }
            j++;
        }
        i++;
    }
}
