/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 04:55:12 by user42            #+#    #+#             */
/*   Updated: 2020/09/22 23:16:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# define _GNU_SOURCE
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include "./philo_one_structures.h"

long int	current_time(t_data data);
void		ft_usleep(int n);
void		ft_putchar(char c);
void		ft_putstr(char *str);
void		ft_putnbr(int nb);
void		*client_thread(void *arg);
int		message_alert(long int time, int index, t_philo *thinker,
					int status);
int			ft_atoi(const char *nptr);
int			ft_strlen(const char *str);
int			return_str(char *str, int ret);
int			init_struct(char **argv, t_data *data);
int			alive_check(t_philo *thinker, t_data *data);
int			init_mutex(t_data *data);
int			init_thinker(t_philo *thinker, t_data *data, int i);

#endif
