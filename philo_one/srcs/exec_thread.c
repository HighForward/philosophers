#include "../includes/philo_one.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void message_alert(long int time, int index, t_philo *thinker, int status)
{
    pthread_mutex_lock(&thinker->data->mutex_msg);
    ft_putstr("\033[1;31m");
    ft_putnbr(time);
    ft_putstr("\033[0m");
    ft_putchar(' ');
    if (status != FED)
    {
        ft_putstr("\033[1;35m");
        ft_putnbr(index);
        ft_putstr("\033[0m");
        ft_putchar(' ');
    }
    ft_putstr("\033[1;32m");
    if (status == EAT)
        write(1, "is eating\n", 10);
    else if (status == SLEEP)
        write(1, "is sleeping\n", 12);
    else if (status == THINK)
        write(1, "is thinking\n", 12);
    else if (status == FORK)
        write (1, "has taken a fork\n", 17);
    else if (status == DIED)
        write (1, "died\n", 5);
    else if (status == FED)
        write (1, "everyone is fed\n", 16);
    ft_putstr("\033[0m");
    pthread_mutex_unlock(&thinker->data->mutex_msg);
}

int alive_check(t_philo *thinker, t_data *data)
{
    int i;

    i = 0;
    while (i < data->nb)
    {
        if (thinker[i].ate >= thinker[i].data->must_eat)
        {
            message_alert(current_time((*data)), i, thinker, FED);
            return (0);
        }
        if (thinker[i].timeout < current_time((*thinker[i].data)) && thinker[i].is_eating == 0)
        {
            message_alert(current_time((*data)), i, thinker, DIED);
            return (0);
        }
        i++;
        usleep(20);
    }
    return (1);
}

void *client_thread(void *arg)
{
    t_philo *now;

    now = (t_philo*)arg;
    while (1)
    {
        message_alert(current_time((*now->data)), now->index, now, FORK);
        now->last_eat = current_time((*now->data));
        now->timeout = now->last_eat + (now->data->die);
        now->is_eating = 1;
        message_alert(current_time((*now->data)), now->index, now, EAT);
        usleep(now->data->eat * 1000);
        now->is_eating = 0;
        now->ate++;
        message_alert(current_time((*now->data)), now->index, now, SLEEP);
        usleep(now->data->sleep * 1000);
        message_alert(current_time((*now->data)), now->index, now, THINK);
    }
}
