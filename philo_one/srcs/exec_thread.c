#include "../includes/philo_one.h"

int alive_check(t_philo *thinker)
{
    int nb;
    int i;

    i = 0;
    nb = thinker[0].data->nb;
    while (i < nb)
    {
        if (thinker[i].ate >= thinker[i].data->must_eat)
            return (0);
        i++;
    }
    return (1);
}

void *client_thread(void *arg)
{
    t_philo *now;

    now = (t_philo*)arg;
    pthread_mutex_lock(&now->mutex);
    while (1)
    {
        printf("%ld %d is eating\n", current_time((*now->data)), now->index);
        usleep(1000 * 1000);
        now->ate++;
        printf("%ld %d is sleeping\n", current_time((*now->data)), now->index);
        usleep(1000 * 1000);
        printf("%ld %d is thinking\n", current_time((*now->data)), now->index);
    }
    pthread_mutex_unlock(&now->mutex);
}
