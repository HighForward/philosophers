/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one_structures.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 04:56:31 by user42            #+#    #+#             */
/*   Updated: 2020/09/22 23:16:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_STRUCTURES_H
# define PHILO_ONE_STRUCTURES_H

# define EAT 1
# define SLEEP 2
# define THINK 3
# define FORK 4
# define DIED 5
# define FED 6

typedef struct		s_fork
{
	pthread_mutex_t	mutex;
	int				i_last_philo;
}					t_fork;

typedef struct		s_data
{
	int				nb;
	int				die;
	int				eat;
	int				sleep;
	int				must_eat;
	int 			nb_rest;
	int 			stop;
	struct timeval	start;
	pthread_mutex_t	mutex_msg;
	t_fork			*forks;
}					t_data;

typedef struct		s_philo
{
	pthread_t		thread;
	pthread_mutex_t	mutex_eat;
	t_data			*data;
	int				index;
	int				is_eating;
	int				total_meal;
	int				timeout;
	int				lfork;
	int				rfork;
}					t_philo;

#endif
