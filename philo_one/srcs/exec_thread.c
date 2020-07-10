#include "../includes/philo_one.h"

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
        if (thinker[i].timeout < current_time((*thinker[i].data)) && thinker[i].is_eating == 0)
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

    now = (t_philo*)arg;
    while (1)
    {

        /************************** deadlock ici =) *******************************/

        pthread_mutex_lock(&now->data->forks[now->rfork]);
        pthread_mutex_lock(&now->data->forks[now->lfork]);


        message_alert(current_time((*now->data)), now->index, now, FORK);
        message_alert(current_time((*now->data)), now->index, now, FORK);


        now->timeout = current_time((*now->data)) + (now->data->die);
        message_alert(current_time((*now->data)), now->index, now, EAT);
        now->is_eating = 1;
        usleep(now->data->eat * 1000);
        now->is_eating = 0;
        now->total_meal++;


        pthread_mutex_unlock(&now->data->forks[now->rfork]);
        pthread_mutex_unlock(&now->data->forks[now->lfork]);

        /************************** deadlock ici =) *******************************/

        message_alert(current_time((*now->data)), now->index, now, SLEEP);
        usleep(now->data->sleep * 1000);
        message_alert(current_time((*now->data)), now->index, now, THINK);
    }
}
