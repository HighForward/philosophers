#include "../includes/philo_two.h"

int is_eating(t_philo thinker)
{
    sem_wait(&thinker.sem_eat);
    if (thinker.is_eating == 0)
    {
        sem_post(&thinker.sem_eat);
        return (0);
    }
    sem_post(&thinker.sem_eat);
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
    t_philo *t;

    t = (t_philo*)arg;
    while (1)
    {

        sem_wait(t->data->take_fork);
        sem_wait(t->data->sem_fork);
        message_alert(current_time((*t->data)), t->index, t, FORK);
        sem_wait(t->data->sem_fork);
        message_alert(current_time((*t->data)), t->index, t, FORK);
        sem_post(t->data->take_fork);

        t->timeout = current_time((*t->data)) + (t->data->die);
        message_alert(current_time((*t->data)), t->index, t, EAT);

        sem_wait(&t->sem_eat);
        t->is_eating = 1;
        usleep(t->data->eat * 1000);
        t->is_eating = 0;
        t->total_meal++;
        sem_post(&t->sem_eat);


        sem_post(t->data->sem_fork);
        sem_post(t->data->sem_fork);


        message_alert(current_time((*t->data)), t->index, t, SLEEP);
        usleep(t->data->sleep * 1000);
        message_alert(current_time((*t->data)), t->index, t, THINK);
    }
}
