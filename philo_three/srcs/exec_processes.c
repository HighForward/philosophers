/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 19:55:12 by mbrignol          #+#    #+#             */
/*   Updated: 2020/09/24 03:09:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

void	*death(void *arg)
{
	t_data *data;

	data = (t_data*)arg;
	sem_wait(data->death);
	data->state = 1;
	sem_post(data->stop);
	return (NULL);
}

void	*alive_check(void *arg)
{
	t_philo *t;

	t = (t_philo*)arg;
	while (1)
	{
		if (t->timeout < current_time((*t->data)) && t->is_eating == 0)
		{
			message_alert(current_time((*t->data)), t->index, t, DIED);
			sem_post(t->data->death);
			exit(EXIT_SUCCESS);
		}
		usleep(30);
	}
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
		sem_wait(t->sem_eat);
		t->is_eating = 1;
		usleep(t->data->eat * 1000);
		t->is_eating = 0;
		t->total_meal++;
		sem_post(t->sem_eat);
		sem_post(data->sem_fork);
		sem_post(data->sem_fork);
		if (t->total_meal >= t->data->must_eat)
			break ;
		message_alert(current_time((*t->data)), t->index, t, SLEEP);
		usleep(t->data->sleep * 1000);
		message_alert(current_time((*t->data)), t->index, t, THINK);
	}
	sem_post(t->data->stop);
	exit(FED);
}

int		create_process(t_data *data, t_philo *t, int i)
{
	t->pid = fork();
	data->pid[i] = t->pid;
	if (t->pid == 0)
	{
		data->sem_msg = sem_open("/sem_msg", O_RDWR);
		data->sem_fork = sem_open("/sem_fork", O_RDWR);
		data->take_fork = sem_open("/take_fork", O_RDWR);
		t->sem_eat = sem_open(t->sem_eat_name, O_RDWR);
		pthread_create(&t->thread, NULL, alive_check, (void*)t);
		pthread_detach(t->thread);
		client_loop(data, t);
	}
	return (0);
}
