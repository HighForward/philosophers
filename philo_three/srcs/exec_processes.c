/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 19:55:12 by mbrignol          #+#    #+#             */
/*   Updated: 2020/09/23 07:57:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

void	*alive_check(void *arg)
{
	t_philo *thinker;

	thinker = (t_philo*)arg;
	while (thinker->stop == 0)
	{
		if (thinker->total_meal >= thinker->data->must_eat && thinker->stop == 0)
		{
			message_alert(current_time((*thinker->data)),
				thinker->index, thinker, FED);
			thinker->stop = 1;
			sem_post(thinker->data->stop);
			sem_post(thinker->data->sem_msg);
			return (NULL);
//			exit(EXIT_SUCCESS);
		}
		if (thinker->timeout < current_time((*thinker->data)) &&
			thinker->is_eating == 0 && thinker->stop == 0)
		{
			message_alert(current_time((*thinker->data)),
				thinker->index, thinker, DIED);
			thinker->stop = 1;
			sem_post(thinker->data->stop);
			sem_post(thinker->data->sem_msg);
			return (NULL);
//			exit(EXIT_SUCCESS);
		}
	}
	return (NULL);
}

void	t_eat(t_data *data, t_philo *thinker)
{
	sem_wait(data->sem_fork);
	message_alert(current_time((*thinker->data)),
		thinker->index, thinker, FORK);
	sem_wait(data->sem_fork);
	message_alert(current_time((*thinker->data)),
		thinker->index, thinker, FORK);
}

void	client_loop(t_data *data, t_philo *thinker)
{
	while (1)
	{
		sem_wait(data->take_fork);
		t_eat(data, thinker);
		sem_post(data->take_fork);
		message_alert(current_time((*thinker->data)),
			thinker->index, thinker, EAT);
		thinker->timeout = current_time((*thinker->data)) +
			(thinker->data->die);
		sem_wait(thinker->sem_eat);
		thinker->is_eating = 1;
		usleep(thinker->data->eat * 1000);
		thinker->is_eating = 0;
		thinker->total_meal++;
		sem_post(thinker->sem_eat);
		sem_post(data->sem_fork);
		sem_post(data->sem_fork);
		message_alert(current_time((*thinker->data)),
			thinker->index, thinker, SLEEP);
		usleep(thinker->data->sleep * 1000);
		message_alert(current_time((*thinker->data)),
			thinker->index, thinker, THINK);
	}
}

int		create_process(t_data *data, t_philo *thinker)
{
	thinker->pid = fork();
	if (thinker->pid == 0)
	{
		data->sem_msg = sem_open("/sem_msg", O_RDWR);
		data->sem_fork = sem_open("/sem_fork", O_RDWR);
		data->take_fork = sem_open("/take_fork", O_RDWR);
		data->stop = sem_open("/stop", O_RDWR);
		data->fed = sem_open("/fed", O_RDWR);
		thinker->sem_eat = sem_open(thinker->sem_eat_name, O_RDWR);
		pthread_create(&thinker->thread, NULL, alive_check, (void*)thinker);
		pthread_detach(thinker->thread);
		client_loop(data, thinker);
		exit(1);
	}
	return (0);
}
