#include "../includes/philo_three.h"

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

int init_semaphore(t_data *data)
{
    sem_init(&data->sem_msg, 0, 1);
    sem_init(&data->sem_fork, 0, data->nb);
}

int init_thinker(t_philo *thinker, t_data *data, int i)
{
    thinker->index = i + 1;
    thinker->data = data;
    thinker->total_meal = 0;
    thinker->is_eating = 0;
    thinker->timeout = data->die;
    thinker->rfork = i;
    thinker->lfork = ((i + 1) == data->nb) ? 0 : (i + 1);
}