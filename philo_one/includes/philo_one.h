#ifndef PHILO_ONE_H
#define PHILO_ONE_H

#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "./philo_one_structures.h"

int		    ft_atoi(const char *nptr);
void	    ft_putstr(char *str);
void	    ft_putnbr(int nb);
int		    ft_strlen(const char *str);
int         return_str(char *str, int ret);
long int    current_time(t_data data);
t_data      init_struct(char **argv);
int         alive_check(t_philo *thinker);
void        *client_thread(void *arg);



#endif