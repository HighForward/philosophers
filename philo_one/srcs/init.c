#include "../includes/philo_one.h"

int	init_struct(char **argv, t_data *data)
{
    data->nb = ft_atoi(argv[0]);
    data->die = ft_atoi(argv[1]);
    data->eat = ft_atoi(argv[2]);
    data->sleep = ft_atoi(argv[3]);
    if (argv[4] != NULL)
        data->must_eat = ft_atoi(argv[4]);
    else
        data->must_eat = 2147483647;
    return (1);
}

int init_mutex(t_data *data)
{
    int i;

    i = 0;
    pthread_mutex_init(&data->mutex_msg, NULL);
    pthread_mutex_unlock(&data->mutex_msg);

    while (i < data->nb)
    {
        data->forks[i] = (pthread_mutex_t)PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP;
        pthread_mutex_unlock(&data->forks[i]);
        i++;
    }
    pthread_mutex_init(&data->take_fork, NULL);
    return (0);
}

int init_thinker(t_philo *thinker, t_data *data, int i)
{
    thinker->index = i + 1;
    thinker->data = data;
    thinker->total_meal = 0;
    thinker->is_eating = 0;
    thinker->timeout = data->die + current_time((*data));
    pthread_mutex_init(&thinker->mutex_eat, NULL);
    pthread_mutex_unlock(&thinker->mutex_eat);
    thinker->rfork = i;
    thinker->lfork = ((i + 1) == data->nb) ? 0 : (i + 1);
}