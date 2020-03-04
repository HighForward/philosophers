#ifndef PHILO_ONE_H
#define PHILO_ONE_H

#include "./philo_one_structures.h"
#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int		ft_atoi(const char *nptr);
void	ft_putstr(char *str);
int		ft_strlen(const char *str);
int		get_thread(t_time time);

#endif