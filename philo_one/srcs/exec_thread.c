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
        if (thinker[i].timeout < current_time((*thinker[i].data)) && is_eating(thinker[i]) == 0)
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
    t_philo *now;
    int ret;

    now = (t_philo*)arg;
    while (1)
    {

        /************************** deadlock ici =) **************************/

        pthread_mutex_lock(&now->data->forks[now->lfork]);
        message_alert(current_time((*now->data)), now->index, now, FORK);
        pthread_mutex_lock(&now->data->forks[now->rfork]);
        message_alert(current_time((*now->data)), now->index, now, FORK);


        now->timeout = current_time((*now->data)) + (now->data->die);
        message_alert(current_time((*now->data)), now->index, now, EAT);

        pthread_mutex_lock(&now->mutex_eat);
        now->is_eating = 1;
        usleep(now->data->eat * 1000);
        now->is_eating = 0;
        now->total_meal++;
        pthread_mutex_unlock(&now->mutex_eat);


        pthread_mutex_unlock(&now->data->forks[now->lfork]);
        pthread_mutex_unlock(&now->data->forks[now->rfork]);

        /************************** deadlock ici =) **************************/

        message_alert(current_time((*now->data)), now->index, now, SLEEP);
        usleep(now->data->sleep * 1000);
        message_alert(current_time((*now->data)), now->index, now, THINK);

    }
}
