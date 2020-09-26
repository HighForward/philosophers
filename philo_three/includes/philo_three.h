/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 20:36:57 by mbrignol          #+#    #+#             */
/*   Updated: 2020/09/26 02:37:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# define _GNU_SOURCE
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "./philo_three_structures.h"

int			ft_atoi(const char *nptr);
void		ft_putchar(char c);
void		ft_putstr(char *str);
void		ft_putnbr(int nb);
int			ft_strlen(const char *str);
int			return_str(char *str, int ret);
long int	current_time(t_data data);
int			init_struct(char **argv, t_data *data);
int			create_process(t_data *data, t_philo *thinker, int i);
void		*alive_check(void *arg);
char		*ft_itoa(int n);
int			init_thinker(t_philo *thinker, t_data *data, int i);
void		message_alert(long int time, int index,
				t_philo *thinker, int status);
int			init_semaphore(t_data *data);
void		*death(void *arg);

#endif
