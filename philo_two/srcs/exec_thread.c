/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrignol <mbrignol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 18:30:34 by mbrignol          #+#    #+#             */
/*   Updated: 2020/09/23 04:35:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

int		alive_check(t_philo *thinker, t_data *data)
{
	int i;

	i = 0;
	while (i < data->nb)
	{
		if (data->nb_rest <= 0)
		{
			message_alert(current_time((*data)), i + 1, thinker, FED);
			return (0);
		}
		if (thinker[i].timeout < current_time((*thinker[i].data)) &&
			thinker[i].is_eating == 0)
		{
			message_alert(current_time((*data)), i + 1, thinker, DIED);
			data->stop = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

void	*client_thread(void *arg)
{
	t_philo *t;

	t = (t_philo*)arg;
	while (1)
	{
		sem_wait(t->data->take_fork);
		sem_wait(t->data->sem_fork);
		if (message_alert(current_time((*t->data)), t->index, t, FORK) == 0)
			break ;
		sem_wait(t->data->sem_fork);
		if (message_alert(current_time((*t->data)), t->index, t, FORK) == 0)
			break ;
		sem_post(t->data->take_fork);
		t->timeout = current_time((*t->data)) + (t->data->die);
		if (message_alert(current_time((*t->data)), t->index, t, EAT) == 0)
			break ;
		sem_wait(&t->sem_eat);
		t->is_eating = 1;
		ft_usleep(t->data->eat * 1000);
		t->is_eating = 0;
		t->total_meal++;
		sem_post(&t->sem_eat);
		sem_post(t->data->sem_fork);
		sem_post(t->data->sem_fork);
		if (t->total_meal >= t->data->must_eat)
			break;
		if (message_alert(current_time((*t->data)), t->index, t, SLEEP) == 0)
			break ;
		ft_usleep(t->data->sleep * 1000);
		if (message_alert(current_time((*t->data)), t->index, t, THINK) == 0)
			break ;
	}
	t->data->nb_rest--;
	return (NULL);
}
