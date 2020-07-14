#ifndef PHILO_TWO_H
#define PHILO_TWO_H

#define _GNU_SOURCE
#include <sys/time.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include "./philo_two_structures.h"

int		    ft_atoi(const char *nptr);
void	    ft_putchar(char c);
void	    ft_putstr(char *str);
void	    ft_putnbr(int nb);
int		    ft_strlen(const char *str);
int         return_str(char *str, int ret);
long int    current_time(t_data data);
int         init_struct(char **argv, t_data *data);
int         alive_check(t_philo *thinker, t_data *data);
void        *client_thread(void *arg);
int         init_thinker(t_philo *thinker, t_data *data, int i);
void        message_alert(long int time, int index, t_philo *thinker, int status);
int        init_semaphore(t_data *data);



#endif