/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three_structures.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 20:39:36 by mbrignol          #+#    #+#             */
/*   Updated: 2020/09/23 07:57:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_STRUCTURES_H
# define PHILO_THREE_STRUCTURES_H

# define EAT 1
# define SLEEP 2
# define THINK 3
# define FORK 4
# define DIED 5
# define FED 6

typedef struct		s_data
{
	int				nb;
	int				die;
	int				eat;
	int				sleep;
	int				must_eat;
	struct timeval	start;
	sem_t			*sem_msg;
	sem_t			*sem_fork;
	sem_t			*take_fork;
	sem_t			*stop;
	sem_t			*fed;
}					t_data;

typedef struct		s_philo
{
	pthread_t		thread;
	sem_t			*sem_eat;
	pid_t			pid;
	t_data			*data;
	char			*sem_eat_name;
	int 			stop;
	int				index;
	int				is_eating;
	int				total_meal;
	int				timeout;
	int				lfork;
	int				rfork;
}					t_philo;

#endif
