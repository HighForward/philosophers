#ifndef PHILO_ONE_H
#define PHILO_ONE_H

#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "./philo_one_structures.h"

int		ft_atoi(const char *nptr);
void	ft_putstr(char *str);
void	ft_putnbr(int nb);
int		ft_strlen(const char *str);
long int    current_time(t_time time);
int     return_str(char *str, int ret);
int		get_thread(t_time time);

void *thread_1(void *arg);

#endif