/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two_structures.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 19:13:26 by mbrignol          #+#    #+#             */
/*   Updated: 2020/09/22 23:16:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_STRUCTURES_H
# define PHILO_TWO_STRUCTURES_H

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
	int 			stop;
	int 			nb_rest;
	struct timeval	start;
	sem_t			*sem_msg;
	sem_t			*sem_fork;
	sem_t			*take_fork;
}					t_data;

typedef struct		s_philo
{
	t_data			*data;
	pthread_t		thread;
	sem_t			*sem_eat;
	char			*sem_eat_name;
	int				index;
	int				is_eating;
	int				total_meal;
	int				timeout;
}					t_philo;

#endif
