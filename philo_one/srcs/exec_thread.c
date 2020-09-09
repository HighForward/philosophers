#include "../includes/philo_one.h"

int is_eating(t_philo thinker)
{
	pthread_mutex_lock(&thinker.mutex_eat);
	if (thinker.is_eating == 0)
	{
		pthread_mutex_unlock(&thinker.mutex_eat);
		return (0);
	}
	pthread_mutex_unlock(&thinker.mutex_eat);
	return (1);
}

int alive_check(t_philo *thinker, t_data *data)
{
	int i;

	i = 0;
	while (i < data->nb)
	{
		if (thinker[i].total_meal >= thinker[i].data->must_eat)
		{
			message_alert(current_time((*data)), i + 1, thinker, FED);
			return (0);
		}
		if (thinker[i].timeout < current_time((*thinker[i].data))
			&& is_eating(thinker[i]) == 0)
		{
			message_alert(current_time((*data)), i + 1, thinker, DIED);
			return (0);
		}
		i++;
	}
	return (1);
}

void *client_thread(void *arg)
{
	t_philo *t;

	t = (t_philo*)arg;
	while (1)
	{
		pthread_mutex_lock(&t->data->take_fork);
		pthread_mutex_lock(&t->data->forks[t->lfork]);
		message_alert(current_time((*t->data)), t->index, t, FORK);
		pthread_mutex_lock(&t->data->forks[t->rfork]);
		message_alert(current_time((*t->data)), t->index, t, FORK);
		pthread_mutex_unlock(&t->data->take_fork);
		t->timeout = current_time((*t->data)) + (t->data->die);
		message_alert(current_time((*t->data)), t->index, t, EAT);
		pthread_mutex_lock(&t->mutex_eat);
		t->is_eating = 1;
		ft_usleep(t->data->eat * 1000);
		t->is_eating = 0;
		t->total_meal++;
		pthread_mutex_unlock(&t->mutex_eat);
		pthread_mutex_unlock(&t->data->forks[t->lfork]);
		pthread_mutex_unlock(&t->data->forks[t->rfork]);
		message_alert(current_time((*t->data)), t->index, t, SLEEP);
		ft_usleep(t->data->sleep * 1000);
		message_alert(current_time((*t->data)), t->index, t, THINK);
	}
}
