/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 04:36:02 by user42            #+#    #+#             */
/*   Updated: 2020/09/26 03:32:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

int		alive_check(t_philo *thinker, t_data *data)
{
	int i;

	i = 0;
	while (i < data->nb)
	{
		if (data->nb_rest <= 0)
		{
			message_alert(current_time((*data)), i, thinker, FED);
			return (0);
		}
		if (thinker[i].timeout < current_time((*thinker[i].data)) &&
			thinker[i].is_eating == 0)
		{
			message_alert(current_time((*data)), i, thinker, DIED);
			data->stop = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

int		t_eat(t_philo *t)
{
	t_fork	*fork;
	int		index;

	index = 0;
	fork = (t->index + index) % 2 ? &t->data->forks[t->lfork]
			: &t->data->forks[t->rfork];
	while (index < 2)
	{
		while (fork->i_last_philo == t->index && t->data->stop == 0)
			;
		pthread_mutex_lock(&fork->mutex);
		if (message_alert(current_time((*t->data)), t->index, t, FORK) == 0)
			return (0);
		fork->i_last_philo = t->index;
		fork = (t->index + (++index)) % 2 ? &t->data->forks[t->lfork]
				: &t->data->forks[t->rfork];
	}
	return (1);
}

void	lets_eat(t_philo *t)
{
	pthread_mutex_lock(&t->mutex_eat);
	t->is_eating = 1;
	ft_usleep(t->data->eat * 1000);
	t->is_eating = 0;
	t->total_meal++;
	pthread_mutex_unlock(&t->data->forks[t->lfork].mutex);
	pthread_mutex_unlock(&t->data->forks[t->rfork].mutex);
	pthread_mutex_unlock(&t->mutex_eat);
}

void	*client_thread(void *arg)
{
	t_philo *t;

	t = (t_philo*)arg;
	while (1)
	{
		if (t_eat(t) == 0)
			break ;
		t->timeout = current_time((*t->data)) + (t->data->die);
		if (message_alert(current_time((*t->data)), t->index, t, EAT) == 0)
			break ;
		lets_eat(t);
		if (t->total_meal >= t->data->must_eat)
			break ;
		if (message_alert(current_time((*t->data)), t->index, t, SLEEP) == 0)
			break ;
		ft_usleep(t->data->sleep * 1000);
		if (message_alert(current_time((*t->data)), t->index, t, THINK) == 0)
			break ;
	}
	t->data->nb_rest--;
	return (NULL);
}
