/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 19:55:12 by mbrignol          #+#    #+#             */
/*   Updated: 2020/09/26 09:21:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

void	*alive_check(void *arg)
{
	t_philo *t;

	t = (t_philo*)arg;
	while (t->data->state != FED)
	{
		if (t->timeout < current_time((*t->data)) && t->is_eating == 0 && t->data->state != FED)
		{
			message_alert(current_time((*t->data)), t->index, t, DIED);
			sem_post(t->data->death);
//			exit(EXIT_SUCCESS);
		}
		usleep(30);
	}
	t->leave_thread = 1;
	return (NULL);
}

void	t_eat(t_data *data, t_philo *t)
{
	sem_wait(data->sem_fork);
	message_alert(current_time((*t->data)), t->index, t, FORK);
	sem_wait(data->sem_fork);
	message_alert(current_time((*t->data)), t->index, t, FORK);
}

void	client_loop(t_data *data, t_philo *t)
{
	while (1)
	{
		sem_wait(data->take_fork);
		t_eat(data, t);
		sem_post(data->take_fork);
		message_alert(current_time((*t->data)), t->index, t, EAT);
		t->timeout = current_time((*t->data)) + (t->data->die);
//		sem_wait(t->sem_eat);
		t->is_eating = 1;
		usleep(t->data->eat * 1000);
		t->is_eating = 0;
		t->total_meal++;
//		sem_post(t->sem_eat);
		sem_post(data->sem_fork);
		sem_post(data->sem_fork);
		if (t->total_meal >= t->data->must_eat)
			break ;
		message_alert(current_time((*t->data)), t->index, t, SLEEP);
		usleep(t->data->sleep * 1000);
		message_alert(current_time((*t->data)), t->index, t, THINK);
	}
	sem_post(data->stop);
	data->state = FED;
	while (t->leave_thread == 0)
		;
	usleep(500);
}
